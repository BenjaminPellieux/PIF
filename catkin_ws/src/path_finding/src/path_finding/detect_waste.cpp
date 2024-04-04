#include "path_finding/detect_waste.hpp"


DetectWaste::DetectWaste(ros::NodeHandle nh) {
    ros::Subscriber position_sub = nh.subscribe("/pif/gps_converted", 100, &DetectWaste::positionCallback, this);
    ros::Subscriber orientation_sub = nh.subscribe("/imu/data", 100, &DetectWaste::orientationCallback, this);
    ros::Subscriber detectWaste_sub = nh.subscribe("/Waste/Pos", 100, &DetectWaste::WastePosCallback, this);

    this->cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    ROS_INFO("detect_waste -> complete.");
}

bool DetectWaste::spin() {
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
        ros::spinOnce();
    }
    return clear;
}

void DetectWaste::go_to_waste() {
    geometry_msgs::Twist cmd_vel;
    bool detected;

    cmd_vel.angular.z = this->detectWaste;
    this->cmd_vel_pub.publish(cmd_vel);

    cmd_vel.linear.x = 0.5;
    double pose_max = this->position.x + DETECT_RANGE;
    while(this->position.x < pose_max) {
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

void DetectWaste::positionCallback(const nav_msgs::Odometry::ConstPtr &position_msg) {
    this->position = position_msg->pose.pose.position;
}

void DetectWaste::orientationCallback(const geometry_msgs::QuaternionStamped::ConstPtr &orientation_msg) {
    this->orientation = orientation_msg->quaternion;
}

void DetectWaste::WastePosCallback(const geometry_msgs::QuaternionStamped::ConstPtr &pos) {
    this->detectWaste = pos->quaternion.z;
}

void DetectWaste::WasteIdCallback(const path_finding::PoseWasteStamped::ConstPtr &msg) {
    this->idWaste = ((msg->data.waste != "NABLE") && (msg->data.waste != "NULL")) ? msg->data : path_finding::PoseWaste();
}
