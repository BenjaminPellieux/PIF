cmake_minimum_required(VERSION 3.5)

project( VisionVideo LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( video3 video3.cpp )
target_link_libraries( video3 ${OpenCV_LIBS} )
