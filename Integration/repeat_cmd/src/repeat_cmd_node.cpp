#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


// DÉCLARATION DES VARIABLES =====================================================================================
geometry_msgs::Twist cmd;

// Other sub and publisher ---------------------------------------------------------------------------------------
ros::Subscriber cmd_sub;
ros::Publisher cmd_pub;

// PROTOTYPES ====================================================================================================
void CallBackFct(const geometry_msgs::Twist &);


// MAIN ==========================================================================================================
int main(int argc, char** argv) {
    ROS_INFO("Starting car control...");

    ROS_INFO("Init ROS...");
    ros::init(argc, argv, "auto_car_ctrl");                                     // Initalisation de ROS
    ROS_INFO("Complete.");

    ROS_INFO("Subscribers and publishers creation...");
    ros::NodeHandle nh;                                                         // Communication ROS

    // Création des subscribers ----------------------------------------------------------------------------------
    cmd_sub = nh.subscribe("/cmd_vel_repeat", 100, &CallBackFct);

    // Création des publishers -----------------------------------------------------------------------------------
    cmd_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 100);
    ROS_INFO("Complete.");

    ROS_INFO("Starting loop.");
    while(true) {
        cmd_pub.publish(cmd);
        ros::spinOnce();                                                        // Boucle de fonctionnement du package
    }
}


// DÉFINITIONS DE FONCTIONS ======================================================================================
/*
description : Fonction callback appelée à chaque modification du topic /cmd_vel_repeat
paramètre : (const, geometry_msgs::Twist::ConstPtr, pointeur) cmd_msg : message reçu.
*/
void CallBackFct(const geometry_msgs::Twist &cmd_msg) {
    cmd.linear.x = cmd_msg.linear.x;
    cmd.angular.z = cmd_msg.angular.z;
}
