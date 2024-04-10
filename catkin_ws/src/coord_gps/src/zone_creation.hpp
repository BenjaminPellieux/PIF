// Include std 
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <iterator>

#include <ros/ros.h>
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/Point32.h>
#include "path_finding/odometry.hpp"


class ZoneDefinition {
private:
    ros::NodeHandle nh;
    ros::Publisher area_pub;

    geometry_msgs::PolygonStamped area;

public:
    ZoneDefinition();
    void addPoint(const geometry_msgs::Point32& point);
};

