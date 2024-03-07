cmake_minimum_required(VERSION 2.8)
project( ImageProc )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(bin/InRangeBlobHSV src/InRangeBlobHSV.cpp)
target_link_libraries(bin/InRangeBlobHSV ${OpenCV_LIBS} )

add_executable(bin/CVVidHoughCircle src/CVVidHoughCircle.cpp)
target_link_libraries(bin/CVVidHoughCircle ${OpenCV_LIBS} )

add_executable(bin/CVVidInRangeBlobHSV src/CVVidInRangeBlobHSV.cpp)
target_link_libraries(bin/CVVidInRangeBlobHSV ${OpenCV_LIBS} )

add_executable(bin/Test_Opencv_exe src/Test_Opencv.cpp )
target_link_libraries(bin/Test_Opencv_exe ${OpenCV_LIBS} )








