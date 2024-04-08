#include "path_finding/check_waste.hpp"


CheckWaste::CheckWaste(ros::NodeHandle nh) : Odometry(nh) {
    this->detectWaste_sub = nh.subscribe("/Waste/Geometry", 100, &CheckWaste::WastePosCallback, this);
    this->haskilens_sub = nh.subscribe("Label/id", 100, &CheckWaste::WasteIdCallback, this);

    this->cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    ROS_INFO("check_waste -> complete.");
}

bool CheckWaste::spin() {
    bool clear = true;
    geometry_msgs::Twist cmd_vel;
    double orientation_max = Odometry::rot + 2.0;
    ros::Rate rate(6);
    
    cmd_vel.angular.z = 0.5;
    while(Odometry::rot < orientation_max) {
        if(this->detectWaste) {
            clear = false;
            break;
        }
        this->cmd_vel_pub.publish(cmd_vel);
        rate.sleep();
        ros::spinOnce();
    }
    return clear;
}

void CheckWaste::go_to_waste() {
    geometry_msgs::Twist cmd_vel;
    bool detected;

    cmd_vel.angular.z = this->detectWaste;
    this->cmd_vel_pub.publish(cmd_vel);

    cmd_vel.linear.x = 0.5;
    double pose_max = Odometry::pose.x + DETECT_RANGE;
    while(Odometry::pose.x < pose_max) {
        if(this->idWaste.waste != "") {
            cmd_vel.linear.x = 0.1;
            cmd_vel.angular.z = std::atan((this->idWaste.center.x - WIDTH_SCREEN) / this->idWaste.center.y);
            detected = true;
        } else if(detected) {
            break;
        } else {
            cmd_vel.angular.z = this->detectWaste;
        }
        this->cmd_vel_pub.publish(cmd_vel);
        ros::spinOnce();
    }
}

void CheckWaste::WastePosCallback(const geometry_msgs::QuaternionStamped::ConstPtr &pos) {
    this->detectWaste = pos->quaternion.z;
}

void CheckWaste::WasteIdCallback(const path_finding::PoseWasteStamped::ConstPtr &msg) {
    this->idWaste = ((msg->data.waste != "NABLE") && (msg->data.waste != "NULL")) ? msg->data : path_finding::PoseWaste();
}
