cmake_minimum_required(VERSION 3.0.2)
project(coord_gps)

find_package(catkin REQUIRED
sensor_msgs
geometry_msgs
roscpp
rospy
)

find_package(catkin REQUIRED
	COMPONENTS roslaunch
)
roslaunch_add_file_check(launch)
