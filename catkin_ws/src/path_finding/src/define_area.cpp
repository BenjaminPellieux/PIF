#include "path_finding/define_area.hpp"


int main(int argc, char **argv) {
    ROS_INFO("Starting PIF package...");
    ROS_INFO("Init ROS...");
    ros::init(argc, argv, "path_finding");
    ROS_INFO("Complete.");

    ros::NodeHandle nh;
    DefineArea define_area(nh);

    ROS_INFO("Starting loop.");
    ros::spin();

    return 0;
}


DefineArea::DefineArea(ros::NodeHandle nh) {
    ros::Subscriber area_sub = nh.subscribe("/area/polygon", 100, &DefineArea::areaCallback, this);
    ros::Subscriber choose_tile_sub = nh.subscribe("/path_finding/pos", 100, &DefineArea::choose_next_tile, this);

    this->grid_pub = nh.advertise<path_finding::GridStamped>("/area/grid", 100);
    this->origin_pub = nh.advertise<geometry_msgs::PointStamped>("/area/origin", 100);
    this->next_tile_pub = nh.advertise<geometry_msgs::PointStamped>("/path_finding/next_tile", 100);

    ROS_INFO("define_area -> complete.");
}

void DefineArea::create_grid() {
    float min_x = this->area.points[0].x,
          min_y = this->area.points[0].y,
          max_x, max_y,
          first_points, next_points;

    grid.header.frame_id = "grid";
    grid.header.stamp = ros::Time::now();

    for(int i=0; i<this->area.points.size(); i++) {
        if(this->area.points[i].x < min_x) {
            min_x = this->area.points[i].x;
        } else if(this->area.points[i].x > max_x) {
            max_x = this->area.points[i].x;
        }
        if(this->area.points[i].y < min_y) {
            min_y = this->area.points[i].y;
        } else if(this->area.points[i].y > max_y) {
            max_y = this->area.points[i].y;
        }
    }
    nbr_subGrid_x = (max_x - min_x) * sqrt(2) / DETECT_RANGE;
    nbr_subGrid_y = (max_y - min_y) * sqrt(2) / DETECT_RANGE;

    for(int i=0; i<nbr_subGrid_y; i++) {
        for(int j=0; j<nbr_subGrid_x; j++) {
            first_points = min_x + j * (DETECT_RANGE / sqrt(2));
            next_points = min_x + (j + 1) * (DETECT_RANGE / sqrt(2));
            this->grid.grid[i][j].sub_area[0].x = first_points;
            this->grid.grid[i][j].sub_area[2].x = first_points;
            if(next_points < max_x) {
                this->grid.grid[i][j].sub_area[1].x = next_points;
                this->grid.grid[i][j].sub_area[3].x = next_points;
            } else {
                this->grid.grid[i][j].sub_area[1].x = max_x;
                this->grid.grid[i][j].sub_area[3].x = max_x;
            }

            first_points = min_y + j * (DETECT_RANGE / sqrt(2));
            next_points = min_y + (j + 1) * (DETECT_RANGE / sqrt(2));
            this->grid.grid[i][j].sub_area[0].y = first_points;
            this->grid.grid[i][j].sub_area[1].y = first_points;
            if(next_points < max_y) {
                this->grid.grid[i][j].sub_area[2].y = next_points;
                this->grid.grid[i][j].sub_area[3].y = next_points;
            } else {
                this->grid.grid[i][j].sub_area[2].y = max_y;
                this->grid.grid[i][j].sub_area[3].y = max_y;
            }
        }
    }
    this->grid_pub.publish(grid);
}

void DefineArea::set_origin() {
    geometry_msgs::PointStamped origin;

    origin.header.frame_id = "origin";
    origin.header.stamp = ros::Time::now();

    origin.point.x = this->area.points[0].x;
    origin.point.y = this->area.points[0].y;
    for(int i=1; i<4; i++) {
        if(abs(this->area.points[i].x) < abs(origin.point.x)) {
            origin.point.x = this->area.points[i].x;
        }
        if(abs(this->area.points[i].y) < abs(origin.point.y)) {
            origin.point.y = this->area.points[i].y;
        }
    }
    this->origin_pub.publish(origin);
}

void DefineArea::choose_next_tile(const geometry_msgs::PointStamped::ConstPtr &pos) {
    int size, move_to_max_x, perimeter, x, y;
    geometry_msgs::PointStamped next_tile;

    next_tile.header.frame_id = "next_tile";
    next_tile.header.stamp = ros::Time::now();

    next_tile.point.x = -1;
    next_tile.point.y = -1;

    for(int ring=0; (ring<=nbr_subGrid_x)&&(ring<=nbr_subGrid_y);ring++) {
        size = 3 + 2 * ring;
        move_to_max_x = 1 + ring;

        x = 0;
        y = -1 - ring;

        perimeter = size * 2 + size * 2 - 4;
        
        for(int n=0; n<perimeter; n++) {
            if((pos.point.x+x >= 0) && (pos.point.y+y >= 0) && (pos.point.x+x <= nbr_subGrid_x) && (pos.point.y+y <= nbr_subGrid_y) && grid.grid[pos.point.y+y][pos.point.x+x].done) {
                next_tile.point.x = pos.point.x + x;
                next_tile.point.y = pos.point.y + y;
                break;
            }
            if((n < move_to_max_x) || (n >= (move_to_max_x + size * 3 - 3))) {
                x++;
            } else if(n < (move_to_max_x + size - 1)) {
                y++;
            } else if(n < (move_to_max_x + size * 2 - 2)) {
                x--;
            } else if(n < (move_to_max_x + size * 3 - 3)){
                y--;
            }
        }
        if((next_tile.point.x != -1) && (next_tile.point.y != -1))
            break;
    }
    this->next_tile_pub.publish(next_tile);
}

void DefineArea::areaCallback(const geometry_msgs::PolygonStamped::ConstPtr &msg) {
    this->area = msg->polygon;
    this->create_grid();
    this->set_origin();
}
