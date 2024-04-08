#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>
#include <algorithm>

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
    ZoneVerification() {
        gps_sub = nh.subscribe("/navsat/fix", 10, &ZoneVerification::gpsCallback, this);
        zone_sub = nh.subscribe("/Area/Point", 10, &ZoneVerification::zoneCallback, this);
        in_zone_pub = nh.advertise<std_msgs::Bool>("/in_zone", 10);
        global_pos_received = false;
    }

    void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &msg) {
        global_pos = *msg;
        global_pos_received = true;
        checkZone();
    }

    void zoneCallback(const geometry_msgs::PointStamped::ConstPtr &msg) {
         geometry_msgs::Point32 point;

    if (msg->header.frame_id == "P0")
    {
        this->Point_tab[0] = (Point){true, msg->point.x, msg->point.y};
        point.x = msg->point.x;
        point.y = msg->point.y;
        area.polygon.points.push_back(point);
    }
    else if (msg->header.frame_id == "P1")
    {
        this->Point_tab[1] = (Point){true, msg->point.x, msg->point.y};
        point.x = msg->point.x;
        point.y = msg->point.y;
        area.polygon.points.push_back(point);
    }
    else if (msg->header.frame_id == "P2")
    {
        this->Point_tab[2] = (Point){true, msg->point.x, msg->point.y};
        point.x = msg->point.x;
        point.y = msg->point.y;
        area.polygon.points.push_back(point);
    }
    else if (msg->header.frame_id == "P3")
    {
        this->Point_tab[3] = (Point){true, msg->point.x, msg->point.y};

        area.header.frame_id = "area";
        area.header.stamp = ros::Time::now();

        point.x = msg->point.x;
        point.y = msg->point.y;
        area.polygon.points.push_back(point);
        
        area_pub.publish(area);
        area.polygon.points.clear();
    }
    checkZone();
    }

    bool ZoneChecker::isInsideRectangle()
    {
        double table_x[4];
        double table_y[4];
        for(uint8_t i = 0; i != 4; i++){
            table_x[i] = this->Point_tab[i].lat;
            table_y[i] = this->Point_tab[i].lon;
        }
        auto min_x = std::min_element(std::begin(table_x),std::end(table_x));
        auto max_x = std::max_element(std::begin(table_x),std::end(table_x));
        auto min_y = std::min_element(std::begin(table_y),std::end(table_y));
        auto max_y = std::max_element(std::begin(table_y),std::end(table_y));
        return (*min_x <= this->global_pos.lat && this->global_pos.lat <= *max_x && *min_y <= this->global_pos.lon && this->global_pos.lon <= *max_y);
    }

    void checkZone() {
        if (global_pos_received) {
            std_msgs::Bool msg;
            if (isInsideRectangle()) {
                msg.data = true;
            } else {
                msg.data = false;
            }
            in_zone_pub.publish(msg);
        }
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "zone_verification");
    ZoneVerification zone_verification;
    ros::spin();
    return 0;
}
