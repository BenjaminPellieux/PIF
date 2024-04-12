#include "Video_Sender.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ros/ros.h>
#include "std_msgs/Bool.h"
#include "std_msgs/UInt16.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/QuaternionStamped.h"
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>



#define IP_SERV "54.36.103.170"
//#define IP_SERV "0.0.0.0"
#define PORT_SERV "7070"
#define MIN_AREA 5
#define MAX_AREA 1000
#define SAT_RANGE 30
#define DEBUG 1


typedef struct{
    int low_h = 0, high_h = 179;
    int low_s = 0, high_s = 255;
    int low_v = 0, high_v = 122;
    int threshold_white = 5; 
}HSVSettings;

class WasteDetection{

    private: 
        cv::VideoCapture cap;
        ros::Publisher detect_pub;
        ros::Publisher vector_waste;
        ros::Publisher pub_obstacle;
        ros::Subscriber moving_status;
        image_transport::Publisher frame_pub;
        
        
        HSVSettings hsvSettings;
        bool obstacle_app;
        bool send_img = false;
        u_int8_t count_area = 1;
        u_int16_t mid_height = 0;
        u_int16_t mid_width = 0;

        cv::Rect closest_rect;
        cv::Mat frame;

        
        cv_bridge::CvImage frame_bridge;
        sensor_msgs::Image frame_msg;
        VideoSender& videoSender_;

    public:
        WasteDetection(VideoSender& videoSender);
        void change_origin();
        void detect_waste();
        void detect_obstacle();
        void run();
        void adjustBrightness(double alpha, int beta);
        void movingCallback(const std_msgs::Bool &msg);
        geometry_msgs::QuaternionStamped calc_geometry_msgs();
};