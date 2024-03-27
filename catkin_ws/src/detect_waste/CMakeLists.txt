cmake_minimum_required(VERSION 3.0.2)
project(detect_waste LANGUAGES CXX )

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  std_msgs
  )
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
	DEPENDS Boost
	CATKIN_DEPENDS geometry_msgs roscpp std_msgs)

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

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME}_node src/detect_waste_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"

set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node ${OpenCV_LIBS} ${catkin_LIBRARIES})
