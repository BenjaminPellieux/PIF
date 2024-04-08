#include <ros/ros.h>
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/Point32.h>

class ZoneDefinition {
private:
    ros::NodeHandle nh;
    ros::Publisher area_pub;

    geometry_msgs::PolygonStamped area;

public:
    ZoneDefinition() {
        area_pub = nh.advertise<geometry_msgs::PolygonStamped>("/area/polygon", 10);
        area.header.frame_id = "area";
        area.header.stamp = ros::Time::now();
    }

    void addPoint(const geometry_msgs::Point32& point) {
        area.polygon.points.push_back(point);
        area_pub.publish(area);
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "zone_definition");
    ZoneDefinition zone_definition;
    ros::spin();
    return 0;
}
