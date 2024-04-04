#include "path_finding/define_area.hpp"


DefineArea::DefineArea(ros::NodeHandle nh) {
    ros::Subscriber area_sub = nh.subscribe("/area/polygon", 100, &DefineArea::areaCallback, this);

    this->grid_pub = nh.advertise<path_finding::GridStamped>("/area/grid", 100);
    this->origin_pub = nh.advertise<geometry_msgs::PointStamped>("/area/origin", 100);
    this->next_tile_pub = nh.advertise<geometry_msgs::PointStamped>("/path_finding/next_tile", 100);

    ROS_INFO("define_area -> complete.");
}

void DefineArea::create_grid(geometry_msgs::Polygon area) {
    float min_x = area.points[0].x,
          min_y = area.points[0].y,
          max_x, max_y,
          first_points, next_points;

    grid.header.frame_id = "grid";
    grid.header.stamp = ros::Time::now();

    for(int i=0; i<area.points.size(); i++) {
        if(area.points[i].x < min_x) {
            min_x = area.points[i].x;
        } else if(area.points[i].x > max_x) {
            max_x = area.points[i].x;
        }
        if(area.points[i].y < min_y) {
            min_y = area.points[i].y;
        } else if(area.points[i].y > max_y) {
            max_y = area.points[i].y;
        }
    }
    nbr_subGrid_x = (max_x - min_x) * sqrt(2) / DETECT_RANGE;
    nbr_subGrid_y = (max_y - min_y) * sqrt(2) / DETECT_RANGE;

    for(int i=0; i<nbr_subGrid_y; i++) {
        path_finding::GridArray subGrid;
        for(int j=0; j<nbr_subGrid_x; j++) {
            path_finding::Grid tile;

            first_points = min_x + j * (DETECT_RANGE / sqrt(2));
            next_points = min_x + (j + 1) * (DETECT_RANGE / sqrt(2));
            tile.sub_area[0].x = first_points;
            tile.sub_area[2].x = first_points;
            if(next_points < max_x) {
                tile.sub_area[1].x = next_points;
                tile.sub_area[3].x = next_points;
            } else {
                tile.sub_area[1].x = max_x;
                tile.sub_area[3].x = max_x;
            }

            first_points = min_y + j * (DETECT_RANGE / sqrt(2));
            next_points = min_y + (j + 1) * (DETECT_RANGE / sqrt(2));
            tile.sub_area[0].y = first_points;
            tile.sub_area[1].y = first_points;
            if(next_points < max_y) {
                tile.sub_area[2].y = next_points;
                tile.sub_area[3].y = next_points;
            } else {
                tile.sub_area[2].y = max_y;
                tile.sub_area[3].y = max_y;
            }
            subGrid.grid.push_back(tile);
        }
        this->grid.grid.push_back(subGrid);
    }
    this->grid_pub.publish(grid);
}

void DefineArea::set_origin(geometry_msgs::Polygon area) {
    geometry_msgs::PointStamped origin;

    origin.header.frame_id = "origin";
    origin.header.stamp = ros::Time::now();

    origin.point.x = area.points[0].x;
    origin.point.y = area.points[0].y;
    for(int i=1; i<4; i++) {
        if(std::abs(area.points[i].x) < std::abs(origin.point.x)) {
            origin.point.x = area.points[i].x;
        }
        if(std::abs(area.points[i].y) < std::abs(origin.point.y)) {
            origin.point.y = area.points[i].y;
        }
    }
    this->origin_pub.publish(origin);
}

geometry_msgs::Point DefineArea::choose_next_tile(geometry_msgs::Point pos) {
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
            if((pos.x+x >= 0) && (pos.y+y >= 0) && (pos.x+x <= nbr_subGrid_x) && (pos.y+y <= nbr_subGrid_y) && grid.grid[pos.y+y].grid[pos.x+x].done) {
                next_tile.point.x = pos.x + x;
                next_tile.point.y = pos.y + y;
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
    return next_tile.point;
}

void DefineArea::areaCallback(const geometry_msgs::PolygonStamped::ConstPtr &msg) {
    this->create_grid(msg->polygon);
    this->set_origin(msg->polygon);
    this->area_recieved = true;
}
