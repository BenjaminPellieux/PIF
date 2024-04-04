
#include <stdio.h>
#include "path_finding/go_to.hpp"

int main (int argc, char **argv)
{
	ros::init(argc, argv, "test_go_to_node");
	
	ros::NodeHandle test;
	Go_To pif_to_to = Go_To(test);
	
	pif_to_to.cmd_pose.x = 10;
	pif_to_to.cmd_pose.y = 10;
	pif_to_to.run();
	
	return 0;
}
