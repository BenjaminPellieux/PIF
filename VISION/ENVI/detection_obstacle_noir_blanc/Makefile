# Makefile for compiling the C++ program with OpenCV

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# OpenCV flags
OPENCV_FLAGS = `pkg-config --cflags --libs opencv4`

# Target executable
TARGET = obstacle_detection

# Source files
SRC = main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): obstacle.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(OPENCV_FLAGS)

clean:
	rm -f $(TARGET)
