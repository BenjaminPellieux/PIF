#include "zone_creation.hpp"
 
ZoneChecker::ZoneChecker()
{
    ros::NodeHandle nh;
    this->gps_sub = nh.subscribe("/navsat/fix", 10, &ZoneChecker::gpsCallback, this);
    this->zone_sub = nh.subscribe("/Area/Point", 10, &ZoneChecker::zoneCallback, this);
    this->polygon_pub = nh.advertise<geometry_msgs::Polygon>("/area/polygon", 10); // Ajout du publisher pour le topic "/area/polygon"
    this->area_pub = nh.advertise<geometry_msgs::PolygonStamped>("/area/polygon", 10);
 
    for(uint8_t i = 0; i != 4; i++){
        this->Point_tab[i].recvd = false; 
    }
}
 
void ZoneChecker::zoneCallback(const geometry_msgs::PointStamped::ConstPtr &msg)
{
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
    publishPolygon();
}
 
void ZoneChecker::publishPolygon()
{
    geometry_msgs::Polygon polygon_msg;
    for(uint8_t i = 0; i < 4; i++) {
        geometry_msgs::Point32 p;
        p.x = this->Point_tab[i].lat;
        p.y = this->Point_tab[i].lon;
        polygon_msg.points.push_back(p);
    }
    polygon_pub.publish(polygon_msg); // Publication du polygon
}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "zone_checker");
    ZoneChecker zone_checker;
    ros::spin();
    return EXIT_SUCCESS;
}
