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
    double target_angle;
    ros::Rate rate(6);
    
    cmd_vel.angular.z = 0.5;
    if(Odometry::rot < 0.0) {
    	target_angle = 0.99;
    	while(Odometry::rot > -0.99) {
    		printf("orientation now : %lf\n", Odometry::rot);
    		this->cmd_vel_pub.publish(cmd_vel);
    		rate.sleep();
    		ros::spinOnce();
    	}
    	
    	cmd_vel.angular.z = -0.1;
    	while(Odometry::rot < target_angle) {
        		if(this->detectWaste) {
            		clear = false;
            		break;
        		}
        		printf("orientation now : %lf, orientation target : %lf\n", Odometry::rot, target_angle);
        		this->cmd_vel_pub.publish(cmd_vel);
        		rate.sleep();
        		ros::spinOnce();
    	}
    } else {
    	target_angle = -0.99;
    	while(Odometry::rot < 0.99) {
    		printf("orientation now : %lf\n", Odometry::rot);
    		this->cmd_vel_pub.publish(cmd_vel);
    		rate.sleep();
    		ros::spinOnce();
    	}
    	
    	cmd_vel.angular.z = 0.1;
    	while(Odometry::rot > target_angle) {
        		if(this->detectWaste) {
            		clear = false;
            		break;
        		}
        		printf("orientation now : %lf, orientation target : %lf\n", Odometry::rot, target_angle);
        		this->cmd_vel_pub.publish(cmd_vel);
        		rate.sleep();
        		ros::spinOnce();
    	}
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
