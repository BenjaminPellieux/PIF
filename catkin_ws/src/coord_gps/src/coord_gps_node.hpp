#include <ros/ros.h>
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/PointStamped.h"
#include "std_msgs/Bool.h"
#include <stdint.h>
#include <algorithm>
#include <iterator>

typedef struct {
    bool recvd; 
    double lon;
    double lat;

}Point;


class ZoneChecker {
    public:
        ZoneChecker();
        void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
        void zoneCallback(const geometry_msgs::PointStamped::ConstPtr& msg);
        bool isInsideRectangle();
        void checkZone();
        bool AllRcvd();


    private:
        ros::Subscriber gps_sub;
        ros::Subscriber zone_sub;
        ros::Publisher in_zone_pub;
        Point global_pos;
        Point Point_tab[4];
};

