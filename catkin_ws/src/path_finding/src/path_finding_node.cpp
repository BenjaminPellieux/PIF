#include "DefineArea.hpp"

// MAIN ==========================================================================================================
int main(int argc, char **argv) {
    ROS_INFO("Starting PIF package...");
    ROS_INFO("Init ROS...");
    ros::init(argc, argv, "DefineArea");                                        // Initalisation de ROS
    ROS_INFO("Complete.");

    DefineArea define_area;

    ROS_INFO("Starting loop.");
    ros::spin();                                                                // Boucle de fonctionnement du package

    return 0;
}


// DÉFINITIONS DE FONCTIONS ======================================================================================
DefineArea::DefineArea() {
    ROS_INFO("Subscribers and publishers creation...");
    ros::NodeHandle nh;                                                         // Communication ROS
    this->area_sub = nh.subscribe("/area/polygon", 100, &DefineArea::areaCallback, this);
    ROS_INFO("Complete.");
}

void DefineArea::create_grid() {
    float min_x = area.points[0].x,
          min_y = area.points[0].y,
          max_x, max_y,
          first_points, next_points;

    // Define max and min among the selected area's points -------------------------------------------------------
    for(int i=0; i<(sizeof(area.points)/sizeof(geometry_msgs::Point32)); i++) {
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
    // Define how many sections there will be --------------------------------------------------------------------
    nbr_subGrid_x = (max_x - min_x) * sqrt(2) / DETECT_RANGE;
    nbr_subGrid_y = (max_y - min_y) * sqrt(2) / DETECT_RANGE;

    // Fill a list which content all sections informations -------------------------------------------------------
    for(int i=0; i<nbr_subGrid_y; i++) {
        for(int j=0; j<nbr_subGrid_x; j++) {
            first_points = min_x + j * (DETECT_RANGE / sqrt(2));
            next_points = min_x + (j + 1) * (DETECT_RANGE / sqrt(2));
            grid[i][j].sub_area[0].x = first_points;
            grid[i][j].sub_area[2].x = first_points;
            if(next_points < max_x) {
                grid[i][j].sub_area[1].x = next_points;
                grid[i][j].sub_area[3].x = next_points;
            } else {
                grid[i][j].sub_area[1].x = max_x;
                grid[i][j].sub_area[3].x = max_x;
            }

            first_points = min_y + j * (DETECT_RANGE / sqrt(2));
            next_points = min_y + (j + 1) * (DETECT_RANGE / sqrt(2));
            grid[i][j].sub_area[0].y = first_points;
            grid[i][j].sub_area[1].y = first_points;
            if(next_points < max_y) {
                grid[i][j].sub_area[2].y = next_points;
                grid[i][j].sub_area[3].y = next_points;
            } else {
                grid[i][j].sub_area[2].y = max_y;
                grid[i][j].sub_area[3].y = max_y;
            }
        }
    }
}

void DefineArea::set_origin() {
    origin.x = area.points[0].x;
    origin.y = area.points[0].y;
    for(int i=1; i<4; i++) {
        if(abs(area.points[i].x) < abs(origin.x)) {
            origin.x = area.points[i].x;
        }
        if(abs(area.points[i].y) < abs(origin.y)) {
            origin.y = area.points[i].y;
        }
    }
}

void DefineArea::choose_next_tile(int posX, int posY) {
    int size, move_to_max_x, perimeter, x, y;
    next_tile.x = -1;
    next_tile.y = -1;

    for(int ring=0; (ring<=nbr_subGrid_x)&&(ring<=nbr_subGrid_y);ring++) {
        size = 3 + 2 * ring;
        move_to_max_x = 1 + ring;

        x = 0;
        y = -1 - ring;

        perimeter = size * 2 + size * 2 - 4;
        
        for(int n=0; n<perimeter; n++) {
            if((posX+x >= 0) && (posY+y >= 0) && (posX+x <= nbr_subGrid_x) && (posY+y <= nbr_subGrid_y) && grid[posY+y][posX+x].done) {
                next_tile.x = posX + x;
                next_tile.y = posY + y;
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
        if((next_tile.x != -1) && (next_tile.y != -1))
            break;
    }
}

void DefineArea::areaCallback(const geometry_msgs::PolygonStamped::ConstPtr& msg) {
    area = msg->polygon;
    this->create_grid();
    this->set_origin();
}
