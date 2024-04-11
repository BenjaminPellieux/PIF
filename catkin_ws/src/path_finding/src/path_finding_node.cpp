#include "path_finding/check_waste.hpp"
#include "path_finding/define_area.hpp"
#include "path_finding/go_to.hpp"

#include <std_msgs/Bool.h>

ros::Subscriber auto_sub;
bool mode;


void  autoCallBack(const std_msgs::Bool::ConstPtr &);


int main(int argc, char **argv) {
    ros::init(argc, argv, "path_finding_node");

    ros::NodeHandle nh;
    DefineArea define_area(nh);
    CheckWaste check_waste(nh);
    Go_To go_to(nh);

    auto_sub = nh.subscribe("/pif/web/controle", 100, &autoCallBack);

    while(ros::ok()) {
        if(!mode) {
            if(define_area.area_recieved) {
                go_to.set_target(define_area.first_tile.x, define_area.first_tile.y);
                printf("Origin : x:%lf y:%lf\nGrid : %ld x %ld\n", define_area.first_tile.x, define_area.first_tile.y, define_area.grid.gridY[0].gridX.size(), define_area.grid.gridY.size());
                if(go_to.run() == 1) {
                    ROS_INFO("Area unreacheable.");
                    go_to.set_target(0.0, 0.0);
                    go_to.run();
                }
                define_area.area_recieved = false;
            } else if((define_area.first_tile.x != 0) && (define_area.first_tile.y != 0)) {
                if(!check_waste.spin()) {
                    check_waste.go_to_waste();
                } else {
                	ROS_INFO("Tile done.");
                    define_area.grid.gridY[define_area.pose_grid.y].gridX[define_area.pose_grid.x].done = true;
                    if(!define_area.choose_next_tile()) {
                        go_to.set_target(define_area.first_tile.x, define_area.first_tile.y);
                        go_to.run();
                        break;
                    }
                    Local_Pose next = define_area.get_next_tile_pose();
                    ROS_INFO("Target next_tile : x:%lf y:%lf", next.x, next.y);
                    go_to.set_target(next.x, next.y);
                }
                if(go_to.run() == 1) {
                    define_area.grid.gridY[define_area.pose_grid.y].gridX[define_area.pose_grid.x].unreachable = true;
                }
            }
        }
        ros::spinOnce();
    }
}


void  autoCallBack(const std_msgs::Bool::ConstPtr &msg) {
    mode = msg->data;
}
