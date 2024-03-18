#include <iostream.h>
#include <ros/ros.h>

ros::Publisher pub;
void lidarCallBackFct(const std_msgs::Bool &);

int main(int argc, char** argv) {
	
	std_msgs::Bool var;

	ros::init(argc, argv, "package");
	ros::NodeHandle nh;
	pub = nh.advertise<std_msgs::Bool>("topic", 100);
	var = true;
	pub.publish(var)
	ros::spin();
	return EXIT_SUCCES;
}
