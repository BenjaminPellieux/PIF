//#include <iostream.h>
#include <ros/ros.h>
#include "sensor_msgs/msg/nav_sat_fix.hpp"
//void lidarCallBackFct(const std_msgs::Bool &);

int main(int argc, char** argv) {
	
	ros::Publisher pub;
	std_msgs::Bool var;

	ros::init(argc, argv, "package");
	ros::NodeHandle nh;
	pub = nh.advertise<std_msgs::Bool>("topic", 100);
	var = true;
	pub.publish(var)
	ros::spin();
	return EXIT_SUCCESS;
}
