#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PointStamped.h>

#ifndef undefined
#define undefined

typedef struct {
    double x;
    double y;
} Local_Pose;


class Odometry {
    protected:
        ros::Subscriber sub_gps;
	    ros::Subscriber sub_odom;

        Local_Pose pose;
        double rot;

        bool pose_called;
        bool rot_called;

        Odometry(ros::NodeHandle);
        void callback_gps(const geometry_msgs::PointStamped::ConstPtr &nav);
        void callback_odom(const sensor_msgs::Imu::ConstPtr &odometry);
};

#endif
