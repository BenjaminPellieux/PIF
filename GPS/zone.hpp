#include <iostream>
#include <fstream>
#include <vector>
#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"

using namespace std;



typedef struct Point {
    double x, y;
}Point;



class Zone(){



    public: 
        
        Point P1,P2,P3,P4;
        bool is_defined = 0;
        void Zone::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
        void Zone::ZoneCallback(const geometry_msgs::PointStamped & msg);
        double Zone::crossProduct(Point A, Point B, Point C);
        bool Zone::isInsideQuadrilateral(Point A, Point B, Point C, Point D, Point P);
