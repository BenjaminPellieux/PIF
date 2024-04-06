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
                define_area.choose_next_tile();
                Local_Pose next = define_area.get_next_tile_pose();
                nav.pose.pose.position.x = next.x;
                nav.pose.pose.position.y = next.y;

                define_area.grid.gridY[define_area.next_tile.y].gridX[define_area.next_tile.x].done = true;
                
                pub_gps.publish(nav);
                i++;
            }
            ROS_INFO("area_recieved : %d", define_area.area_recieved);
            ros::spinOnce();
        }
        return 0;
    } else {
        ROS_INFO("Node needs 1 arguments : the number of iteration to make.");
        return -1;
    }
}
