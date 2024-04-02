#define _USE_MATH_DEFINES

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"

#include <cmath>
#include <math.h>
#include <sstream>
#include <sensor_msgs/NavSatStatus.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Pose.h>
#include <visualization_msgs/Marker.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#define TEST_POS_ORIGIN_LAT	49.98487
#define TEST_POS_ORIGIN_LON	1.70135

#define RANGE_GOOD_ENOUGH	1

#define SPEED_FWD	1.0

#define TRY_LEFT	-1
#define TRY_RIGHT	1
#define NO_OBS		0

typedef struct {
    double x;
    double y;
}Local_Pose;


class Go_To{
    public:
        Local_Pose pose;
        double r_z;
        Local_Pose cmd_pose;
        
        double obs_dist;
        double obs_ang;

        bool gps_called = false;
        bool called = false;
        bool called_obs = false;
        bool cant_go_to;


        Go_To();
        void callback_obs(const visualization_msgs::Marker::ConstPtr &mark);
        void callback_gps(const nav_msgs::Odometry::ConstPtr &nav);
        void callback_odom(const nav_msgs::Odometry::ConstPtr &odometry);
        void callback_cmd(const geometry_msgs::Pose::ConstPtr &cmd);

        bool in_range();
        int get_cmd_from_obs(double *coef_x,
	double *accel_z,
	double *obs_try,
	int *try_nb,
	double *target_ang,
	uint8_t dist_at_begin);
        void run();
    private: 

        ros::NodeHandle pos_xy;
        ros::Subscriber sub_gps;
        ros::Subscriber sub_odom;
        ros::Subscriber sub_cmd;
        ros::Subscriber sub_laser;
        ros::Publisher cmd_xy; 

};
