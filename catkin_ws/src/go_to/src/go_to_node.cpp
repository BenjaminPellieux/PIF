#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"

#include <math.h>
#include <sstream>
#include <sensor_msgs/NavSatStatus.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Pose.h>
#include <visualization_msgs/Marker.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_POS_ORIGIN_LAT	49.98487
#define TEST_POS_ORIGIN_LON	1.70135

#define RANGE_GOOD_ENOUGH	1

#define SPEED_FWD	1.0

#define TRY_LEFT		-1
#define TRY_RIGHT		1
#define NO_OBS		0

double x;
double y;
double r_z;

double cmd_x = 0;
double cmd_y = 0;

double obs_dist;
double obs_ang;

uint8_t gps_called = 0;
uint8_t called = 0;
uint8_t called_obs = 0;

uint8_t cant_go_to;

void callback_obs(const visualization_msgs::Marker::ConstPtr &mark)
{
	if (!called_obs)
		called_obs = 1;
		
	if (mark->pose.orientation.z > 0) {
		obs_ang = mark->pose.orientation.z;
	} else {
		obs_ang = mark->pose.orientation.z + 2; 
	}
	obs_dist = mark->scale.x;
}

void callback_gps(const nav_msgs::Odometry::ConstPtr &nav)
{
	if (gps_called == 0)
		gps_called = 1;
		
	x = nav->pose.pose.position.x;
	y = nav->pose.pose.position.y;
}

void callback_odom(const nav_msgs::Odometry::ConstPtr &odometry)
{
	if (odometry->pose.pose.orientation.z > 0) {
		r_z = odometry->pose.pose.orientation.z;
	} else {
		r_z = odometry->pose.pose.orientation.z + 2; 
	}
	
	if (!called)
		called = 1;
}

void callback_cmd(const geometry_msgs::Pose::ConstPtr &cmd)
{
	cmd_x = cmd->position.x;
	cmd_y = cmd->position.y;
}

int in_range() {
	int in;
	
	if ((x < cmd_x + RANGE_GOOD_ENOUGH)
		&& (x > cmd_x - RANGE_GOOD_ENOUGH)
		&& (y < cmd_y + RANGE_GOOD_ENOUGH)
		&& (y > cmd_y - RANGE_GOOD_ENOUGH)) {
		in = 1;
	} else {
		in = 0;
	}
	return in;
}

int get_cmd_from_obs(double *coef_x, double *accel_z, double *obs_try, int *try_nb, double *size_try, double *target_ang)
{
	int ret = 0;

	
		if (called_obs) {
		
			printf("obs angle : %lf\n", obs_ang);
			printf("obs dist : %lf\n", obs_dist);
			called_obs = 0;
			
			if (obs_dist == 0) {
				//nothing
				*coef_x = 1;
			} else if (obs_dist < 1) { //if too close
				*coef_x = 0;//stop
			} else if (obs_dist < 2) {
				//if obstacle 
				
				if (*try_nb == NO_OBS) {
					*try_nb++;
					*size_try = sqrt(((cmd_x - x) * (cmd_x - x)) + ((cmd_y - y) * (cmd_y - y))) + 10;
					if (obs_ang > 0) {
						*obs_try = TRY_RIGHT;
					} else {
						*obs_try = TRY_LEFT;
					}
				} 
				
				if (*try_nb) {
					*coef_x = obs_dist - 0.5;
					if (*size_try < sqrt(((cmd_x - x) * (cmd_x - x)) + ((cmd_y - y) * (cmd_y - y)))) {
						*size_try = *size_try + 10;
						
						if (*try_nb == 2) 
							return -1;
						*try_nb++;
						*obs_try = *obs_try * (- 1);
						*coef_x = 0;
					}
					
					*target_ang += ((1 - (obs_dist - 1)) * (obs_ang + ((- *obs_try) / 2))) + ((obs_dist - 1) * *target_ang);
					printf("coef dist : %lf\nnew target : %lf\n", (obs_dist - 1), *target_ang);
					*coef_x = (1 - (obs_dist - 1)) + 0.01;
				}
			} else {
				*obs_try = 0;
				*try_nb = 0;
				*coef_x = 1;
			}
			
			
		}
		
	return ret;
}

int main(int argc, char *argv[])
{

	//FILE *file_raw;
	//file_raw = fopen("/home/ros/catkin_ws/src/pif_go_to/test.txt", "a");

	//geometry_msgs::Point pos;
		
	ros::init(argc, argv, "pif_go_to_node");
	
	ros::NodeHandle pos_xy;

	printf("trying to subscribe to /odometry/filtered and /pif_cmd...\n");
	ros::Subscriber sub_gps = pos_xy.subscribe("/odometry/gps", 1000, callback_gps);
	ros::Subscriber sub_odom = pos_xy.subscribe("/odometry/filtered", 1000, callback_odom);
	ros::Subscriber sub_cmd = pos_xy.subscribe("/pif_cmd", 1000, callback_cmd);
	ros::Subscriber sub_laser = pos_xy.subscribe("/obstacle_marker", 1000, callback_obs);
	printf("subscribed\n");
	ros::Publisher cmd_xy = pos_xy.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
	//ros::Publisher dir_xy = pos_xy.advertise<geometry_msgs::Twist>("/dir_vel", 1);
	//ros::Publisher origin = gps_xy.advertise<geometry_msgs::Point>("/pif/gps_origin", 1000);
		
    	geometry_msgs::Twist msg;
    	
    	double op_adj;
    	double accel = 0;
    	double dist;
    	double obs_try = 0; //TRY_LEFT, TRY_RIGHT, NO_OBS
    	int try_nb = 0;
    	
    	double obs_coef_x;
    	double obs_accel_z;
    	double size_try;
    	
	while (ros::ok())
	{
		sleep(0.5);
		if (called && gps_called) {
			gps_called = 0;
			called = 0;
			printf("x : %lf\ny : %lf\nr_z : %lf\n", x, y, r_z);
			printf("cmd x : %lf\ncmd y : %lf\n", cmd_x, cmd_y);
			if (in_range()) {
				msg.linear.x = 0;
				msg.angular.z = 0;
				accel = 0;
			} else {
				if (((cmd_x - x) < 0) && ((cmd_y - y) > 0)) {
					op_adj = - (atan((cmd_x - x)/(cmd_y - y)) / 3.14) + 0.5;
					//ok
				} else if ((cmd_x - x) < 0) {
					op_adj = - (atan((cmd_x - x)/(cmd_y - y)) / 3.14) + 1.5;
					
				} else if (((cmd_x - x) > 0) && ((cmd_y - y) > 0)) {
					op_adj = atan((cmd_y - y)/(cmd_x - x)) / 3.14;
					//ok
				} else {
					op_adj = (atan((cmd_y - y)/(cmd_x - x)) / 3.14) + 2;
					
				}
				if (get_cmd_from_obs(&obs_coef_x, &obs_accel_z, &obs_try, &try_nb, &size_try, &op_adj) < 0) {
					cant_go_to = 1;
					//stop ?
				}
				
				msg.angular.z = op_adj - r_z;
				
				if (msg.angular.z > 1)
					msg.angular.z = msg.angular.z - 2;
					
				dist = sqrt(((cmd_x - x) * (cmd_x - x)) + ((cmd_y - y) * (cmd_y - y)));
				
				if ((accel < 0.1) && (dist > 1))
					accel = accel + 0.001;
				
				msg.linear.x = ((accel * sqrt(((cmd_x - x) * (cmd_x - x)) + ((cmd_y - y) * (cmd_y - y)))) / 2) * obs_coef_x;
				
				if (msg.linear.x >= 1) 
					msg.linear.x = 1;
				
				msg.angular.z = msg.angular.z * 2;
				
				printf("rov angular : %lf\n", r_z);
				printf("point angle : %lf\n", op_adj);
				printf("cmd angle : %lf\n", msg.angular.z);
				printf("accel : %lf\n", accel);
				
			}
			cmd_xy.publish(msg);
		}
		ros::spinOnce();
	}

	return 0;
}
