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
                // WARNING may need to change the formula
                go_to.set_target(define_area.origin.x + DETECT_RANGE / std::sqrt(2), define_area.origin.y + DETECT_RANGE / std::sqrt(2));
                go_to.run();
                define_area.area_recieved = false;
            } else if((define_area.origin.x != 0) && (define_area.origin.y != 0)) {
                if(!check_waste.spin()) {
                    check_waste.go_to_waste();
                } else {
                    // WARNING if function to end the loop : is there an other tile left ?
                    define_area.choose_next_tile();
                    Local_Pose next = define_area.get_next_tile_pose();
                    go_to.set_target(next.x, next.y);
                }
                go_to.run();
            }
        }
        ros::spinOnce();
    }
}


void  autoCallBack(const std_msgs::Bool::ConstPtr &msg) {
    mode = msg->data;
}
