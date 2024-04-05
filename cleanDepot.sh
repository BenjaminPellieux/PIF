#! /bin/bash

declare todelet=$(find . \( -name "CMakeFiles" -o -name "CMakeCache.txt" -o -name "Makefile" -o -name "catkin_generated" -o -name "build" \))
echo $todelet 
rm -rf $todelet


