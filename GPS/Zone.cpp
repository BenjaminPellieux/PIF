#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/PointStamped.h>
#include <iostream>
#include <cmath>

class Zone {
public:
    double global_latitude;
    double global_longitude;
    geometry_msgs::Point P1;
    geometry_msgs::Point P2;
    geometry_msgs::Point P3;
    geometry_msgs::Point P4;

    Zone() {
        global_latitude = 0.0;
        global_longitude = 0.0;
    }

    void gps_callback(const sensor_msgs::NavSatFix::ConstPtr& msg) {
        // Callback appelée lors de la réception de messages GPS
        global_latitude = msg->latitude;
        global_longitude = msg->longitude;
        ROS_INFO("Coordonnées GPS : Latitude = %f, Longitude = %f", global_latitude, global_longitude);
    }

    bool is_inside_rectangle(const geometry_msgs::Point& A, const geometry_msgs::Point& B, const geometry_msgs::Point& C, const geometry_msgs::Point& D, const geometry_msgs::Point& P) {
        // Vérifier si le point est à l'intérieur du rectangle ABCD
        double min_x = std::min({A.x, B.x, C.x, D.x});
        double max_x = std::max({A.x, B.x, C.x, D.x});
        double min_y = std::min({A.y, B.y, C.y, D.y});
        double max_y = std::max({A.y, B.y, C.y, D.y});
        return (min_x <= P.x && P.x <= max_x && min_y <= P.y && P.y <= max_y);
    }

    void zone_callback(const geometry_msgs::PointStamped::ConstPtr& msg) {
        geometry_msgs::Point point = msg->point;
        if (msg->header.frame_id == "P1") {
            P1 = point;
        } else if (msg->header.frame_id == "P2") {
            P2 = point;
        } else if (msg->header.frame_id == "P3") {
            P3 = point;
        } else if (msg->header.frame_id == "P4") {
            P4 = point;
        }
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "zone_node");
    ros::NodeHandle nh;
    Zone zone;

    ros::Subscriber gps_sub = nh.subscribe("/NavSat/fix", 10, &Zone::gps_callback, &zone);
    ros::Subscriber zone_sub = nh.subscribe("/Area/Point", 10, &Zone::zone_callback, &zone);

    ros::spin();

    return 0;
}
