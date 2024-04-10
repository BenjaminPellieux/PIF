// Include std 
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <iterator>

#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>
#include <algorithm>
#include "path_finding/odometry.hpp"

class ZoneVerification {
private:
    ros::NodeHandle nh;
    ros::Subscriber gps_sub;
    ros::Subscriber zone_sub;
    ros::Publisher in_zone_pub;

    geometry_msgs::Point32 Point_tab[4];
    bool global_pos_received;
    sensor_msgs::NavSatFix global_pos;

public:
    ZoneVerification();
    void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &msg);
    void zoneCallback(const geometry_msgs::PointStamped::ConstPtr &msg);
    bool isInsideRectangle();
    void checkZone();
};


