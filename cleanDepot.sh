#! /bin/bash

declare todelet=$(find . \( -name "CMakeFiles" -o -name "CMakeCache.txt" -o -name "Makefile" -o -name "catkin_generated" -o -name "build" \))
declare exectodelet=$(find . -type f -exec file {} + | grep "ELF" | cut -d: -f1)
echo $todelet $exectodelet 
rm -rf $todelet $exectodelet


