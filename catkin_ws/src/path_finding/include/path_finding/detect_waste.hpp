#include "path_finding/odometry.hpp"

#include <ros/ros.h>
#include <unistd.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <path_finding/PoseWasteStamped.h>
#include <path_finding/PoseWaste.h>


#define DETECT_RANGE 12.0
#define WIDTH_SCREEN 320
#define HEIGHT_SCREEN 240


class DetectWaste : public Odometry {
private:
    ros::Publisher cmd_vel_pub;
    float detectWaste;
    path_finding::PoseWaste idWaste;
public:
    DetectWaste(ros::NodeHandle);
    bool spin();
    void go_to_waste();

    void WastePosCallback(const geometry_msgs::QuaternionStamped::ConstPtr &);
    void WasteIdCallback(const path_finding::PoseWasteStamped::ConstPtr &);
};
