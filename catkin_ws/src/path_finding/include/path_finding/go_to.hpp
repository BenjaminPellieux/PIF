#define _USE_MATH_DEFINES

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "path_finding/odometry.hpp"

#include <cmath>
#include <math.h>
#include <sstream>
#include <sensor_msgs/NavSatStatus.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Pose.h>
<<<<<<< HEAD
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Quaternion.h>
=======
>>>>>>> 0b949d28773dff8622021b58d2a2983cc2a15580
#include <geometry_msgs/Point.h>
#include <visualization_msgs/Marker.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#define RANGE_GOOD_ENOUGH	2

#define SPEED_FWD	1.0

#define TRY_LEFT	-1
#define TRY_RIGHT	1
#define NO_OBS		0


class Go_To : public Odometry {
    public:
        Local_Pose cmd_pose;
        
        double obs_dist;
        double obs_ang;

        bool called_obs = false;

        Go_To(ros::NodeHandle);
        void callback_obs(const visualization_msgs::Marker::ConstPtr &mark);
<<<<<<< HEAD
        void callback_gps(const nav_msgs::Odometry::ConstPtr &nav);
        void callback_odom(const geometry_msgs::QuaternionStamped::ConstPtr &odometry);
=======
>>>>>>> 0b949d28773dff8622021b58d2a2983cc2a15580

        bool in_range();
        int modify_target_from_lidar(double *coef_x,
                                     double *accel_z,
                                     double *obs_try,
                                     int *try_nb,
                                     double *target_ang,
                                     uint8_t dist_at_begin);
        int run();

    private:
<<<<<<< HEAD
	ros::Subscriber sub_gps;
	ros::Subscriber sub_odom;
	ros::Subscriber sub_laser;
	ros::Publisher cmd_xy;
=======
        ros::Subscriber sub_laser;
        ros::Publisher cmd_xy;
>>>>>>> 0b949d28773dff8622021b58d2a2983cc2a15580
};
