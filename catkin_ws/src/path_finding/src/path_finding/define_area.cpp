#include "path_finding/define_area.hpp"


DefineArea::DefineArea(ros::NodeHandle nh) : Odometry(nh) {
    this->area_recieved = false;

    this->area_sub = nh.subscribe("/area/polygon", 100, &DefineArea::areaCallback, this);

    this->grid_pub = nh.advertise<path_finding::GridStamped>("/area/grid", 100);
    this->origin_pub = nh.advertise<geometry_msgs::PointStamped>("/area/origin", 100);
    this->pose_grid_pub = nh.advertise<geometry_msgs::PointStamped>("/area/pose_grid", 100);

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
    this->nbr_subGrid_x = (max_x - min_x) * sqrt(2) / DETECT_RANGE;
    this->nbr_subGrid_y = (max_y - min_y) * sqrt(2) / DETECT_RANGE;

    for(int i=0; i<this->nbr_subGrid_y; i++) {
        path_finding::GridArray subGrid;
        for(int j=0; j<this->nbr_subGrid_x; j++) {
            path_finding::Grid tile;

            first_points = min_x + j * (DETECT_RANGE / sqrt(2));
            next_points = min_x + (j + 1) * (DETECT_RANGE / sqrt(2));
            tile.top_left.x = first_points;
            if(next_points < max_x) {
                tile.bottom_right.x = next_points;
            } else {
                tile.bottom_right.x = max_x;
            }

            first_points = min_y + j * (DETECT_RANGE / sqrt(2));
            next_points = min_y + (j + 1) * (DETECT_RANGE / sqrt(2));
            tile.top_left.y = first_points;
            if(next_points < max_y) {
                tile.bottom_right.y = next_points;
            } else {
                tile.bottom_right.y = max_y;
            }
            subGrid.gridX.push_back(tile);
        }
        this->grid.gridY.push_back(subGrid);
    }
    this->grid_pub.publish(grid);
}

void DefineArea::set_origin(geometry_msgs::Polygon area) {
    this->origin.header.frame_id = "origin";
    this->origin.header.stamp = ros::Time::now();

    this->origin.point.x = area.points[0].x;
    this->origin.point.y = area.points[0].y;
    for(int i=1; i<4; i++) {
        if(std::abs(area.points[i].x) < std::abs(this->origin.point.x)) {
            this->origin.point.x = area.points[i].x;
        }
        if(std::abs(area.points[i].y) < std::abs(this->origin.point.y)) {
            this->origin.point.y = area.points[i].y;
        }
    }
    this->origin_pub.publish(this->origin);
}

void DefineArea::pos_in_grid() {
    this->pose_grid.header.frame_id = "pose_grid";
    this->pose_grid.header.stamp = ros::Time::now();

    for(int y=0; y<this->nbr_subGrid_y; y++) {
        if((this->grid.gridY[y].gridX[0].top_left.y < Odometry::pose.y) && (Odometry::pose.y < this->grid.gridY[y].gridX[0].bottom_right.y)) {
            this->pose_grid.point.y = y;
            break;
        }
    }
    for(int x=0; x<this->nbr_subGrid_x; x++) {
        if((this->grid.gridY[0].gridX[x].top_left.x < Odometry::pose.x) && (Odometry::pose.x < this->grid.gridY[0].gridX[x].bottom_right.x)) {
            this->pose_grid.point.x = x;
            break;
        }
    }
    this->pose_grid_pub.publish(this->pose_grid);
}

void DefineArea::choose_next_tile() {
    int size, move_to_max_x, perimeter, x, y;

    this->pos_in_grid();

    this->next_tile.x = -1;
    this->next_tile.y = -1;

    for(int ring=0; (ring<=this->nbr_subGrid_x)&&(ring<=this->nbr_subGrid_y);ring++) {
        size = 3 + 2 * ring;
        move_to_max_x = 1 + ring;

        x = 0;
        y = -1 - ring;

        perimeter = size * 2 + size * 2 - 4;
        
        for(int n=0; n<perimeter; n++) {
            if((this->pose_grid.point.x+x >= 0) && (this->pose_grid.point.y+y >= 0)
                    && (this->pose_grid.point.x+x <= this->nbr_subGrid_x) && (this->pose_grid.point.y+y <= this->nbr_subGrid_y)
                    && !this->grid.gridY[this->pose_grid.point.y+y].gridX[this->pose_grid.point.x+x].done
                    && !this->grid.gridY[this->pose_grid.point.y+y].gridX[this->pose_grid.point.x+x].unreachable) {
                this->next_tile.x = this->pose_grid.point.x + x;
                this->next_tile.y = this->pose_grid.point.y + y;
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
            
            ros::spinOnce();
        }
        if((this->next_tile.x != -1) && (this->next_tile.y != -1))
            break;
    }
}

Local_Pose DefineArea::get_next_tile_pose() {
    Local_Pose next_tile_center;

    next_tile_center.x = (this->grid.gridY[this->next_tile.y].gridX[this->next_tile.x].bottom_right.x - this->grid.gridY[this->next_tile.y].gridX[this->next_tile.x].top_left.x) / 2;
    next_tile_center.y = (this->grid.gridY[this->next_tile.y].gridX[this->next_tile.x].bottom_right.y - this->grid.gridY[this->next_tile.y].gridX[this->next_tile.x].top_left.y) / 2;

    return next_tile_center;
}


void DefineArea::areaCallback(const geometry_msgs::PolygonStamped::ConstPtr &msg) {
    this->create_grid(msg->polygon);
    this->set_origin(msg->polygon);
    this->area_recieved = true;
}