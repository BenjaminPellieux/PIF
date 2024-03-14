cmake_minimum_required(VERSION 3.0.2)
project(coord_gps)

find_package(catkin REQUIRED
sensor_msgs
geometry_msgs
roscpp
)
include_directories(
	include
	${catkin_INCLUDE_DIRS}
)
add_executable(${PROJECT_NAME}_node src/coord_gps_node.cpp)
target_link_libraries(${PROJECT_NAME}_node
	${catkin_LIBRARIES}
)

find_package(catkin REQUIRED
	COMPONENTS roslaunch
)
roslaunch_add_file_check(launch)
