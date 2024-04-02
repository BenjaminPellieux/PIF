#include "coord_gps_node.hpp"

ZoneChecker::ZoneChecker()
{
    ros::NodeHandle nh;
    this->gps_sub = nh.subscribe("/navsat/fix", 10, &ZoneChecker::gpsCallback, this);
    this->zone_sub = nh.subscribe("/Area/Point", 10, &ZoneChecker::zoneCallback, this);
    this->in_zone_pub = nh.advertise<std_msgs::Bool>("/in_zone", 10);
    this->global_pos = (Point) {false, 0.0, 0.0};
    for(uint8_t i ; i != 4; i++){
        this->Point_tab[i].recvd  = false; 
    }
}

void ZoneChecker::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &msg)
{
    this->global_pos = (Point) {true, msg->latitude, msg->longitude};
    checkZone();
}

void ZoneChecker::zoneCallback(const geometry_msgs::PointStamped::ConstPtr &msg)
{
    if (msg->header.frame_id == "P0")
    {
        this->Point_tab[0] = (Point){true, msg->point.x, msg->point.y};
    }
    else if (msg->header.frame_id == "P1")
    {
        this->Point_tab[1] = (Point){true, msg->point.x, msg->point.y};
    }
    else if (msg->header.frame_id == "P2")
    {
        this->Point_tab[2] = (Point){true, msg->point.x, msg->point.y};
    }
    else if (msg->header.frame_id == "P3")
    {
        this->Point_tab[3] = (Point){true, msg->point.x, msg->point.y};
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

void ZoneChecker::checkZone()
{
   
    if (AllRcvd())
    {
        std_msgs::Bool msg;
        if (isInsideRectangle())
        {   
            msg.data = true;
        }
        else
        {
            msg.data = false;
        }
        in_zone_pub.publish(msg);
    }
}

bool ZoneChecker::AllRcvd(){
    for (uint8_t i; i != 4; i++){
        if(! this->Point_tab[i].recvd){
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "zone_checker");
    ZoneChecker zone_checker;
    ros::spin();
    return 0;
}
