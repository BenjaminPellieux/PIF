CXX = g++
CXXFLAGS = -std=c++11 -Wall
OPENCV_LIBS = `pkg-config --cflags --libs opencv4`

TARGET = vision_pixel_par_pixel

all: $(TARGET)

$(TARGET): vision.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(OPENCV_LIBS)

clean:
	rm -f $(TARGET)
