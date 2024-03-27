cmake_minimum_required(VERSION 3.0.2)
project(coord_gps LANGUAGES CXX)

find_package(catkin REQUIRED COMPONENTS
	sensor_msgs
	std_msgs
	geometry_msgs
	roscpp
)

#find_package(catkin REQUIRED 
	#	COMPONENTS roslaunch
	#)

catkin_package(
	CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs std_msgs)
message( "found catkin: ${catkin_FOUND}" )
include_directories(${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_node src/coord_gps_node.cpp)

set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME gps_node PREFIX "")

target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
#roslaunch_add_file_check(launch)
