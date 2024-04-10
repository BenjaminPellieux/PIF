#include "path_finding/odometry.hpp"


Odometry::Odometry(ros::NodeHandle nh) {
    this->pose = (Local_Pose) {0.0, 0.0};

	this->sub_gps = nh.subscribe("/pif/gps_converted", 1000, &Odometry::callback_gps, this);
	this->sub_odom = nh.subscribe("/pif/magneto/data", 1000, &Odometry::callback_odom, this);
}

void Odometry::callback_gps(const geometry_msgs::PointStamped::ConstPtr &nav) {
	if(!this->pose_called)
		this->pose_called = true;

	this->pose.x = nav->point.x;
	this->pose.y = nav->point.y;
}

void Odometry::callback_odom(const std_msgs::Float32::ConstPtr &odometry) {
	this->rot = -odometry->data;
	
	if (!this->rot_called)
		this->rot_called = true;
}
