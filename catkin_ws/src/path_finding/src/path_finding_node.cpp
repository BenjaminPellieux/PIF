#include "path_finding/define_area.hpp"
#include "path_finding/detect_waste.hpp"
#include "path_finding/go_to.hpp"


int main(int argc, char **argv) {
    ROS_INFO("Starting PIF package...");
    ROS_INFO("Init ROS...");
    ros::init(argc, argv, "auto_car_ctrl");
    ROS_INFO("Complete.");
    
    ROS_INFO("Subscribers and publishers creation...");
    ros::NodeHandle nh;

    Go_To go_to(nh);
    DefineArea define_area(nh);
    DetectWaste detect_waste(nh);

    ROS_INFO("Complete.");

    int ErrRun;

    ROS_INFO("Starting loop.");
    while(ros::ok()) {
        ErrRun = go_to.run();
        if(ErrRun < 0) {
            ROS_INFO("Erreur during go_to running.");
            break;
        }
        ros::spinOnce();
    }
    ROS_INFO("Ending program.");
}
