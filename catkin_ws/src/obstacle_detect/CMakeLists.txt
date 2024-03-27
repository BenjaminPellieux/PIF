cmake_minimum_required(VERSION 3.0.2)
project(obstacle_detect)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)
find_package(OpenCV REQUIRED)

## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
	CATKIN_DEPENDS roscpp std_msgs)

###########
## Build ##
###########


message( "found catkin: ${catkin_FOUND}" ) # shows '1'
message( "roscpp include_dir: ${roscpp_INCLUDE_DIRS}" ) # shows *nothing*
message( "OpenCV include_dir: ${OpenCV_INCLUDE_DIRS}" ) # shows *nothing*

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories( ${catkin_INCLUDE_DIRS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/obstacle_detect.cpp
# )

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME}_node src/obstacle_detect_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node ${OpenCV_LIBS} ${catkin_LIBRARIES})

