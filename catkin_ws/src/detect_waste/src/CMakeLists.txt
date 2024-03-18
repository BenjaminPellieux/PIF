cmake_minimum_required(VERSION 3.5)


project( VisionVideoSat LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs)
find_package( OpenCV REQUIRED )



message( "found catkin: ${catkin_FOUND}" ) # shows '1'
message( "roscpp include_dir: ${roscpp_INCLUDE_DIRS}" ) # shows *nothing*

catkin_package(
  CATKIN_DEPENDS geometry_msgs
)


include_directories(${catkin_INCLUDE_DIRS})
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( VisionVideoSat VisionVideoSat.cpp )
target_link_libraries( VisionVideoSat ${OpenCV_LIBS} ${catkin_LIBRARIES} )
