#include "Video_Sender.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ros/ros.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/QuaternionStamped.h"



//#define IP_SERV "10.8.0.1"
#define IP_SERV "0.0.0.0"
#define PORT_SERV "7070"
#define MIN_AREA 5
#define MAX_AREA 1000
#define SAT_RANGE 30
#define DEBUG 0



class WasteDetection{

    private: 
        cv::VideoCapture cap;
        ros::NodeHandle nh;
        ros::Publisher detect_pub;
        ros::Publisher vector_waste;
        

        bool send_img = false;
        u_int8_t count_area = 1;
        u_int16_t mid_height = 0;
        u_int16_t mid_width = 0;

        cv::Rect closest_rect;
        cv::Mat frame;
        VideoSender& videoSender_;

    public:
        WasteDetection(VideoSender& videoSender);
        void change_origin();
        void run();
        geometry_msgs::QuaternionStamped calc_geometry_msgs();
};