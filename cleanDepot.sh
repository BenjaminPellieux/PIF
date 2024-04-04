#! /bin/bash


echo $(find . \( -name "CMakeFiles" -o -name "CMakeCache.txt" -o -name "Makefile" -o -name "catkin_generated" \))  
rm -rf $(find . \( -name "CMakeFiles" -o -name "CMakeCache.txt" -o -name "Makefile" -o -name "catkin_generated" \))


