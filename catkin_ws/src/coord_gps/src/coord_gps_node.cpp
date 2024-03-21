#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/PointStamped.h"
#include "std_msgs/Bool.h"

class ZoneChecker {
public:
    ZoneChecker() {
        ros::NodeHandle nh;
        gps_sub = nh.subscribe("/NavSat/fix", 10, &ZoneChecker::gpsCallback, this);
        zone_sub = nh.subscribe("/Area/Point", 10, &ZoneChecker::zoneCallback, this);
        in_zone_pub = nh.advertise<std_msgs::Bool>("/in_zone", 10);
        global_latitude = 0.0;
        global_longitude = 0.0;
        P1_received = false;
        P2_received = false;
        P3_received = false;
        P4_received = false;
    }

    void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg) {
        global_latitude = msg->latitude;
        global_longitude = msg->longitude;
        checkZone();
    }

    void zoneCallback(const geometry_msgs::PointStamped::ConstPtr& msg) {
        if (msg->header.frame_id == "P1") {
            P1_received = true;
            P1_x = msg->point.x;
            P1_y = msg->point.y;
        } else if (msg->header.frame_id == "P2") {
            P2_received = true;
            P2_x = msg->point.x;
            P2_y = msg->point.y;
        } else if (msg->header.frame_id == "P3") {
            P3_received = true;
            P3_x = msg->point.x;
            P3_y = msg->point.y;
        } else if (msg->header.frame_id == "P4") {
            P4_received = true;
            P4_x = msg->point.x;
            P4_y = msg->point.y;
        }
        checkZone();
    }

    bool isInsideRectangle(double A_x, double A_y, double B_x, double B_y,
                           double C_x, double C_y, double D_x, double D_y,
                           double P_x, double P_y) {
        double min_x = std::min({A_x, B_x, C_x, D_x});
        double max_x = std::max({A_x, B_x, C_x, D_x});
        double min_y = std::min({A_y, B_y, C_y, D_y});
        double max_y = std::max({A_y, B_y, C_y, D_y});
        return (min_x <= P_x && P_x <= max_x && min_y <= P_y && P_y <= max_y);
    }

    void checkZone() {
        if (P1_received && P2_received && P3_received && P4_received) {
            if (isInsideRectangle(P1_x, P1_y, P2_x, P2_y, P3_x, P3_y, P4_x, P4_y,
                                  global_latitude, global_longitude)) {
                std_msgs::Bool msg;
                msg.data = true;
                in_zone_pub.publish(msg);
            } else {
                std_msgs::Bool msg;
                msg.data = false;
                in_zone_pub.publish(msg);
            }
        }
    }

private:
    ros::Subscriber gps_sub;
    ros::Subscriber zone_sub;
    ros::Publisher in_zone_pub;
    double global_latitude;
    double global_longitude;
    bool P1_received;
    bool P2_received;
    bool P3_received;
    bool P4_received;
    double P1_x;
    double P1_y;
    double P2_x;
    double P2_y;
    double P3_x;
    double P3_y;
    double P4_x;
    double P4_y;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "zone_checker");
    ZoneChecker zone_checker;
    ros::spin();
    return 0;
}
