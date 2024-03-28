#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <sensor_msgs/NavSatStatus.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Pose.h>
#include <unistd.h>
#include <sys/types.h>

#define NBR_SAMPLE	64

#define TEST_POS_ORIGIN_LAT	48.984871
#define TEST_POS_ORIGIN_Y	1.701388

#define POS_GPS	0
#define NBR_CLOSE	1
#define NBR_MAX_VAL_HIGHEST	10	//if not working, increase one by one to allow more position close 
				//maybe if samples are not that volatile
#define INRANGE_MAX_CALIB	((double)0.0000001) //increase if samples are too far away from each other


uint8_t callback_called = 0;

double lat_in;
double long_in;
double lat_origin_diff = 0;
double long_origin_diff = 0;

void callback_gps(const sensor_msgs::NavSatFixConstPtr& fix)
{
	//ROS_INFO("Xin = %lf\nYin = %lf\n", fix->latitude, fix->longitude);
	
	if (!callback_called)
		callback_called = 1;
		

	long_in = fix->longitude;
	lat_in = fix->latitude;
}

int get_most_sampled_value(double *lat_cal, double *long_cal, uint8_t cal)
{

	uint32_t nbr_call_sample = 0;
	int spike_detected = 0;
	double lat_cal_arr[NBR_SAMPLE];
	double long_cal_arr[NBR_SAMPLE];
	uint32_t close_arr[NBR_SAMPLE];
	int stacked_highest = 0;
	int stacked_highest_equal_nbr = 0;
	int stacked_highest_value = 0;
	
	//starting calibration
	
	
	for (int n = 0; (n < 100) && (spike_detected == 0); n++) { //loop or timeout (more of a nb try max)
	
		printf("Calibration running...\n");
		
		while (ros::ok() && (nbr_call_sample < (cal ? NBR_SAMPLE : 64)))
		{	
			//get NBR_SAMPLE samples 
			ros::spinOnce();
				
			if (callback_called) {
						
				lat_cal_arr[nbr_call_sample] = lat_in;
				long_cal_arr[nbr_call_sample] = long_in;
				
				//printf("sample float = %.14lf\t sample n : %d\n", lat_cal_arr[nbr_call_sample], nbr_call_sample);
				callback_called = 0;
				
				nbr_call_sample++;
				
			}
		}
		
		
		for (int i = 0; i < (cal ? NBR_SAMPLE : 64); i++) {
			close_arr[i] = 0;
			for (int j = 0; j < (cal ? NBR_SAMPLE : 64); j++) {
				//for each i, search for an other sample close in a range INRANGE_MAX_CALIB
				//count them in close_arr[i]
				if ((lat_cal_arr[j] <= lat_cal_arr[i] + (INRANGE_MAX_CALIB * n))
				&& (lat_cal_arr[j] >= lat_cal_arr[i] - (INRANGE_MAX_CALIB * n))
				&& (long_cal_arr[j] <= long_cal_arr[i] + (INRANGE_MAX_CALIB * n))
				&& (long_cal_arr[j] >= long_cal_arr[i] - (INRANGE_MAX_CALIB * n))) {
					close_arr[i] = close_arr[i] + 1;
				}
				//printf("to compare : %0.14lf\t smaller than : %0.14lf\t higher than : %0.14lf\t nbr true : %d\n", lat_cal_arr[j], lat_cal_arr[i] + INRANGE_MAX_CALIB, lat_cal_arr[i] - INRANGE_MAX_CALIB, close_arr[i]);
				
			}
		}
		
		stacked_highest = 0;
		stacked_highest_equal_nbr = 0;
		stacked_highest_value = 0;
		//if the higher founded sample is alone of his kind, it means it has the highest probably to be the correct pos
		for (int i = 0; i < (cal ? NBR_SAMPLE : 64); i++) {
			if (close_arr[i] > close_arr[stacked_highest]) {
				stacked_highest = i;
				stacked_highest_value = close_arr[i];
			} else if ((close_arr[i] == close_arr[stacked_highest]) && (close_arr[i] != 0.0)) {
				stacked_highest_equal_nbr++;
			}
			
			
		}
		if (stacked_highest_value == 0) {
			spike_detected == 2;
		} else if (stacked_highest_equal_nbr <= NBR_MAX_VAL_HIGHEST) {
			spike_detected = 1;
			*long_cal = long_cal_arr[stacked_highest];
			*lat_cal = lat_cal_arr[stacked_highest];
		}
		
		printf("highest found n : %d\t highest found coord : %.14lf\t highest found nbr : %d\n", stacked_highest, lat_cal_arr[stacked_highest], close_arr[stacked_highest]);
		
	}
	if (spike_detected == 0) {
		printf("Too many similar sample increase NBR_MAX_VAL_HIGHEST n in area : %d \n", stacked_highest_equal_nbr);
	} else if (spike_detected == 2) {
		printf("Samples too far away from each other increase INRANGE_MAX_CALIB\n");
	}
	
	return spike_detected;
}

int main(int argc, char **argv)
{
	geometry_msgs::Point pos;
	
	ros::init(argc, argv, "gps_convert_node");
	
	ros::NodeHandle gps_xy;

	ros::Subscriber sub = gps_xy.subscribe("/navsat/fix", 1000, callback_gps);
	ros::Publisher gps_pub = gps_xy.advertise<geometry_msgs::Point>("/pif/gps_xy", 1000);
	//ros::Publisher origin = gps_xy.advertise<geometry_msgs::Point>("/pif/gps_origin", 1000);

	double  lat, lon;
	uint8_t cal = 1;
	if (get_most_sampled_value(&lat, &lon, cal) == 1) {
		pos.x = lat;
		pos.y = lon;
		//origin.publish(pos);
		lat_origin_diff = lat - TEST_POS_ORIGIN_LAT;
		long_origin_diff = lon - TEST_POS_ORIGIN_Y;
		cal = 0;
		printf("Success!\n");
		while (ros::ok())
		{
			if (get_most_sampled_value(&lat, &lon, cal) == 1) {
				pos.x = lat + lat_origin_diff;
				pos.y = lon + long_origin_diff;
		
				ROS_INFO("running...");
			
				gps_pub.publish(pos);
			}
		}
		
	} else {
		printf("failed !\n");
	}
	
	

	return 0;
}
