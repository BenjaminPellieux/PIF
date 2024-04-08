#include <stdlib.h>
#include "path_finding/define_area.hpp"

int main (int argc, char **argv) {
    int i = 0;
    nav_msgs::Odometry nav;
	
    if(argc == 2) {
        ros::init(argc, argv, "test_define_area_node");

        ros::NodeHandle test;
        DefineArea define_area(test);

        ros::Publisher pub_gps = test.advertise<nav_msgs::Odometry>("/pif/gps_converted", 100);

        while(ros::ok()) {
            if(i > (int)*argv[0])
                break;
            if(define_area.area_recieved) {
                for(int i=0; i<define_area.grid.gridY.size(); i++) {
                    for(int j=0; j<define_area.grid.gridY[0].gridX.size(); j++) {
                        if((j == define_area.first_tile.x) && (i == define_area.first_tile.y)) {
                            printf("< >");
                        } else {
                            printf("[ ]");
                        }
                    }
                    printf("\n");
                }
                printf("origin : x => %lf, y => %lf", define_area.first_tile.x, define_area.first_tile.y);

                nav.pose.pose.position.x = define_area.first_tile.x + DETECT_RANGE / std::sqrt(2);
                nav.pose.pose.position.y = define_area.first_tile.y + DETECT_RANGE / std::sqrt(2);

                define_area.grid.gridY[define_area.first_tile.y].gridX[define_area.first_tile.x].done = true;
                pub_gps.publish(nav);

                define_area.area_recieved = false;
            } else if((define_area.first_tile.x != 0) && (define_area.first_tile.y != 0)) {
                define_area.choose_next_tile();
                Local_Pose next = define_area.get_next_tile_pose();
                nav.pose.pose.position.x = next.x;
                nav.pose.pose.position.y = next.y;

                define_area.grid.gridY[define_area.next_tile.y].gridX[define_area.next_tile.x].done = true;
                
                pub_gps.publish(nav);
                printf("position dans grille : largeur => %lf, hauteur => %lf", define_area.pose_grid.x, define_area.pose_grid.y);
                i++;
            }
            ros::spinOnce();
        }
        return 0;
    } else {
        ROS_INFO("Node needs 1 arguments : the number of iteration to make.");
        return -1;
    }
}
