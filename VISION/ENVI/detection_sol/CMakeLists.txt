cmake_minimum_required(VERSION 3.0)
project(video2.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(OpenCV 4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(video2 video2.cpp)
target_link_libraries(video2 ${OpenCV_LIBS})
