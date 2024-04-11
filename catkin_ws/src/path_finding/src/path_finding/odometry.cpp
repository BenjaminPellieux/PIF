#include "path_finding/odometry.hpp"


Odometry::Odometry(ros::NodeHandle nh) {
    this->pose = (Local_Pose) {0.0, 0.0};

#ifdef SIMU
	this->sub_odom = nh.subscribe("/odometry/filtered", 1000, &Odometry::callback_odom, this);
#else 
	this->sub_odom = nh.subscribe("/pif/magneto/data", 1000, &Odometry::callback_odom, this);
#endif
	this->sub_gps = nh.subscribe("/pif/gps_converted", 1000, &Odometry::callback_gps, this);
}

void Odometry::callback_gps(const geometry_msgs::PointStamped::ConstPtr &nav) {
	if(!this->pose_called)
		this->pose_called = true;

	this->pose.x = nav->point.x;
	this->pose.y = nav->point.y;
}
#ifdef SIMU
void Odometry::callback_odom(const nav_msgs::Odometry::ConstPtr &odometry) {
	this->rot = odometry->pose.pose.orientation.z;
#else
void Odometry::callback_odom(const std_msgs::Float32::ConstPtr &odometry) {
	this->rot = odometry->data;
#endif
	if (!this->rot_called)
		this->rot_called = true;
}
