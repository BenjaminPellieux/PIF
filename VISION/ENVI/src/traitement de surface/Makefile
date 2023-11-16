CXX = g++
CXXFLAGS = -std=c++11 -Wall
OPENCV_FLAGS = `pkg-config --cflags --libs opencv4`

SRC = vision.cpp
EXECUTABLE = vision

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OPENCV_FLAGS)

clean:
	rm -f $(EXECUTABLE)
