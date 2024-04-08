// Include std 
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <iterator> 
 
// ROS
#include <ros/ros.h>

// ROS TOPIC 
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/PolygonStamped.h"
#include "geometry_msgs/Point32.h"
#include "std_msgs/Bool.h"
#include "path_finding/odometry.hpp"

// Définition du type Point
typedef struct {
    bool recvd; 
    double lon;
    double lat;

}Point;

// Définition de la Class ZoneCheker 
class ZoneChecker:  public Odometry{
    // Definition en Public des méthodes de la classe ZoneCheker
    public:
        ZoneChecker(ros::NodeHandle nh); // Constructor
        void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
        void zoneCallback(const geometry_msgs::PointStamped::ConstPtr& msg);
        bool isInsideRectangle();
        void checkZone();
        bool AllRcvd();

    // Definition des propriétés de la classe ZoneCheker 
    private:
        ros::Subscriber zone_sub;
        ros::Publisher in_zone_pub;
        ros::Publisher area_pub;
        Point global_pos;
        Point Point_tab[4];
        geometry_msgs::PolygonStamped area;
};

