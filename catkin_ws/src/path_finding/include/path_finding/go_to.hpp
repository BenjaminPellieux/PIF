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
#include <geometry_msgs/Point.h>
#include <std_msgs/Bool.h>
#include <visualization_msgs/Marker.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#define RANGE_GOOD_ENOUGH	2

#define INNACCESSIBLE_COUNTER_MAX	100

#define SPEED_FWD	1.0

#define TRY_LEFT	-1
#define TRY_RIGHT	1
#define NO_OBS		0


class Go_To : public Odometry {
    public:
        double obs_dist;
        double obs_ang;

        bool called_obs = false;

        Go_To(ros::NodeHandle);
        void callback_obs(const visualization_msgs::Marker::ConstPtr &mark);

        bool in_range();
        int modify_target_from_lidar(double *coef_x,
                                     double *accel_z,
                                     double *obs_try,
                                     int *try_nb,
                                     double *target_ang,
                                     uint8_t dist_at_begin);
        int run();
        void set_target(double, double);

    private:
        ros::Subscriber sub_laser;
        ros::Publisher cmd_xy;
        ros::Publisher moving;

        Local_Pose cmd_pose;
};
