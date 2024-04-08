#include "coord_gps_node.hpp"

ZoneChecker::ZoneChecker(ros::NodeHandle nh) : Odometry(nh)
{
    this->zone_sub = nh.subscribe("/Area/Point", 10, &ZoneChecker::zoneCallback, this);
    this->in_zone_pub = nh.advertise<std_msgs::Bool>("/in_zone", 10);
    this->area_pub = nh.advertise<geometry_msgs::PolygonStamped>("/area/polygon", 10);

    for(uint8_t i ; i != 4; i++){
        this->Point_tab[i].recvd  = false; 
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
        this->area.polygon.points.push_back(point);
    }
    else if (msg->header.frame_id == "P1")
    {
        this->Point_tab[1] = (Point){true, msg->point.x, msg->point.y};
        point.x = msg->point.x;
        point.y = msg->point.y;
        this->area.polygon.points.push_back(point);
    }
    else if (msg->header.frame_id == "P2")
    {
        this->Point_tab[2] = (Point){true, msg->point.x, msg->point.y};
        point.x = msg->point.x;
        point.y = msg->point.y;
        this->area.polygon.points.push_back(point);
    }
    else if (msg->header.frame_id == "P3")
    {
        this->Point_tab[3] = (Point){true, msg->point.x, msg->point.y};

        point.x = msg->point.x;
        point.y = msg->point.y;

        this->area.header.frame_id = "area";
        this->area.header.stamp = ros::Time::now();
        this->area.polygon.points.push_back(point);
        
        this->area_pub.publish(this->area);
        this->area.polygon.points.clear();
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
    return (*min_x <= this->pose.x && this->pose.x <= *max_x \
            && *min_y <= this->pose.y && this->pose.y <= *max_y);
}

void ZoneChecker::checkZone()
{
   
    if ((this->pose.x) && (AllRcvd()))
    {
        std_msgs::Bool msg;
        if (isInsideRectangle()){   
            msg.data = true;

        }
        else{
            msg.data = false;
        }
        in_zone_pub.publish(msg); // Publication du polygon
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
    ros::NodeHandle nh;
    ZoneChecker zone_checker = ZoneChecker(nh);
    ros::spin();
    return EXIT_SUCCESS;
}
