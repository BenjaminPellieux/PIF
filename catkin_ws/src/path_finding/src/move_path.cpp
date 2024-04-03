#include "path_finding/move_path.hpp"


int main(int argc, char **argv) {
    ROS_INFO("Starting PIF package...");
    ROS_INFO("Init ROS...");
    ros::init(argc, argv, "auto_car_ctrl");
    ROS_INFO("Complete.");
    
    ROS_INFO("Subscribers and publishers creation...");
    ros::NodeHandle nh;

    MovePath move_path(nh);

    ROS_INFO("Starting loop.");
    ros::spin();
}


MovePath::MovePath(ros::NodeHandle nh) {
    ros::Subscriber position_sub = nh.subscribe("/odometry/filtered_map", 100, &positionCallback);
    ros::Subscriber orientation_sub = nh.subscribe("/imu/data", 100, &orientationCallback);
    ros::Subscriber detectWaste_sub = nh.subscribe("/Waste/Pos", 100, &WastePosCallback);

    this->cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    ROS_INFO("move_path -> complete.");
}

bool MovePath::spin() {
    bool clear = true;
    geometry_msgs::Twist cmd_vel;
    double orientation_max = this->orientation.z + 2.0;
    ros::Rate rate(5);
    
    cmd_vel.angular.z = 0.5;
    while(this->orientation.z < orientation_max) {
        if(this->detectWaste) {
            clear = false;
            break;
        }
        this->cmd_vel_pub.publish(cmd_vel);
        rate.sleep();
    }
    return clear;
}

void MovePath::go_to_waste() {
    geometry_msgs::Twist cmd_vel;
    bool detected;

    cmd_vel.angular.z = this->detectWaste;
    this->cmd_vel_pub.publish(cmd_vel);

    cmd_vel.linear.x = 0.5;
    double pose_max = this->position.x + DETECT_RANGE;
    while(this->position.x < pose_max) {
        if(this->idWaste.waste) {
            cmd_vel.linear.x = 0.1;
            cmd_vel.angular.z = std::atan((this->idWaste.center.x - WIDTH_SCREEN) / this->isWaste.center.y);
            detected = true;
        } else if(detected) {
            break;
        } else {
            cmd_vel.angular.z = this->detectWaste;
        }
        this->cmd_vel_pub.publish(cmd_vel);
    }
}

void MovePath::positionCallback(const geometry_msgs::PoseStamped::ConstPtr &position_msg) {
    this->position = position_msg;
}

void MovePath::orientationCallback(const geometry_msgs::QuaternionStamped::ConstPtr &orientation_msg) {
    this->orientation = orientation_msg.orientation;
}

void MovePath::WastePosCallback(const geometry_msgs::QuaternionStamped::ConstPtr &pos) {
    this->detectWaste = pos.quaternion.z;
}

void MovePath::WasteIdCallback(const path_finding::PoseWasteStamped::ConstPtr &msg) {
    this->idWaste = ((msg.data.waste != "NABLE") && (msg.data.waste != "NULL")) ? msg.data : path_finding::PoseWaste();
}