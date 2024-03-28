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
#include "std_msgs/Bool.h"

// Definition du type Point
typedef struct {
    bool recvd; 
    double lon;
    double lat;

}Point;

// Definition de la Class ZoneCheker 
class ZoneChecker {
    // Definition en Public des methodes de la classe ZoneCheker
    public:
        ZoneChecker(); // Constructor
        void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
        void zoneCallback(const geometry_msgs::PointStamped::ConstPtr& msg);
        bool isInsideRectangle();
        void checkZone();
        bool AllRcvd();

    // Definition des propriéte de la classe ZoneCheker 
    private:
        ros::Subscriber gps_sub;
        ros::Subscriber zone_sub;
        ros::Publisher in_zone_pub;
        Point global_pos;
        geometry_msgs::PolygonStamped Point_tab;
};

