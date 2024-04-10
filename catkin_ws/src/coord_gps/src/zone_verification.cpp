#include "zone_verification.hpp"
 
ZoneChecker::ZoneChecker()
{
    ros::NodeHandle nh;
    this->gps_sub = nh.subscribe("/navsat/fix", 10, &ZoneChecker::gpsCallback, this);
    this->in_zone_pub = nh.advertise<std_msgs::Bool>("/in_zone", 10);
 
    this->global_pos = (Point) {false, 0.0, 0.0};
    for(uint8_t i = 0; i != 4; i++){
        this->Point_tab[i].recvd  = false; 
    }
}
 
void ZoneChecker::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &msg)
{
    this->odometry = (Point) {true, msg->x, msg->y};
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
    return (*min_x <= this->odometry.x && this->odometry.x <= *max_x && *min_y <= this->odometry.y && this->odometry.y <= *max_y);
}
 
void ZoneChecker::checkZone()
{
    if ((this->odometry.recvd) && (AllRcvd()))
    {
        std_msgs::Bool msg;
        if (isInsideRectangle()){   
            msg.data = true;
        }
        else{
            msg.data = false;
        }
        in_zone_pub.publish(msg);
    }
}
 
bool ZoneChecker::AllRcvd(){
    for (uint8_t i = 0; i != 4; i++){
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
    return EXIT_SUCCESS;
}
