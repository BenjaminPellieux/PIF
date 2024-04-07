#include "path_finding/odometry.hpp"


Odometry::Odometry(ros::NodeHandle nh) {
    this->pose = (Local_Pose) {0.0, 0.0};

	this->sub_gps = nh.subscribe("/pif/gps_converted", 1000, &Odometry::callback_gps, this);
	this->sub_odom = nh.subscribe("/imu/data", 1000, &Odometry::callback_odom, this);
}

void Odometry::callback_gps(const geometry_msgs::Point::ConstPtr &nav) {
	if(!this->pose_called)
		this->pose_called = true;

	this->pose.x = nav->x;
	this->pose.y = nav->y;
}

void Odometry::callback_odom(const sensor_msgs::Imu::ConstPtr &odometry) {
	this->rot = odometry->orientation.z;
	
	if (!this->rot_called)
		this->rot_called = true;
}
