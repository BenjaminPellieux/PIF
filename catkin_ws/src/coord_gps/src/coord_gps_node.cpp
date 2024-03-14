#include "ros/ros.h"


ros::Subscriber sub;

int main (int argc, char** argv){
    //Initialiser le noeud ROS
    ros::init(argc, argv, "coor_gps");
    //Créer un objet NodeHandle pour communiquer avec le système ROS
    ros::NodeHandle nh;
    sub = nh.subscribe("/topic", 100, &poseCallback)
   //Maintenir le noeud en cours d'exécution
    ros::spin();
}

void poseCallback(const std_msgs::Bool &message){
    std::cout << message << std::endl;

    return 0;
}

ROS_INFO("Position de la zone - x:%f,y:%f", msg->x, msg->y);