#include "path_finding/go_to.hpp"


Go_To::Go_To(ros::NodeHandle nh) : Odometry(nh) {
	this->cmd_pose = (Local_Pose) {0.0, 0.0};
	this->sub_laser = nh.subscribe("/obstacle_marker", 1000, &Go_To::callback_obs, this);

	this->cmd_xy = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
	this->moving = nh.advertise<std_msgs::Bool>("/pif/moving", 1);

	ROS_INFO("go_to -> complete.");
}

void Go_To::callback_obs(const visualization_msgs::Marker::ConstPtr &mark) {
	if (! this->called_obs)
		this->called_obs = true;
		
	this->obs_ang = mark->pose.orientation.z;
	this->obs_dist = mark->scale.x;
}

bool Go_To::in_range() {
	if ((Odometry::pose.x < this->cmd_pose.x + RANGE_GOOD_ENOUGH)
			&& (Odometry::pose.x > this->cmd_pose.x - RANGE_GOOD_ENOUGH)
			&& (Odometry::pose.y < this->cmd_pose.y + RANGE_GOOD_ENOUGH)
			&& (Odometry::pose.y > this->cmd_pose.y - RANGE_GOOD_ENOUGH)) {
		return 1;
	} else {
		return 0;
	}
}

int Go_To::modify_target_from_lidar(double *coef_x,
						double *accel_z,
						double *obs_try,
						int *try_nb,
						double *target_ang) {
	int ret = 0;
	double angle_to_add;

	double old_target_angle;
			
	if (obs_dist == 0) {
		//nothing
		*obs_try = 0;
		*try_nb = 0;
		*coef_x = 1;
	} else if (obs_dist < 1) { //if too close
		*coef_x = 0;//stop
	} else if (obs_dist < 2.5) {
		if (obs_dist < 2) {
			//if obstacle 
			ret = 1;
			if (*try_nb == NO_OBS) {
				*try_nb++;
				if (obs_ang < 0) {
					*obs_try = TRY_RIGHT;
					printf("obs on right\n");
				} else {
					*obs_try = TRY_LEFT;
					printf("obs on left\n");
				}
			} 
			
			if (*try_nb) {
				if (obs_ang > 0.6)
					obs_ang = 0.6;
				if (obs_ang < -0.6)
					obs_ang = - 0.6;
				
				if (obs_ang > 0) {
					*target_ang = obs_ang - 0.6;
				} else {
					*target_ang = obs_ang + 0.6;
				}
				//ROS_INFO("new target = %lf", *target_ang);
				
				if (*target_ang > 1) 
					*target_ang - 2;
				if (*target_ang < -1) 
					*target_ang + 2;
			}	
		}
		
		*coef_x = (obs_dist - 1) * 0.66;
		
	} else {
		*obs_try = 0;
		*try_nb = 0;
		*coef_x = 1;
	}
		
	return ret;
}

int Go_To::run()
{
	geometry_msgs::Twist msg;
	std_msgs::Bool is_moving;
	ros::Rate rate(6);
	int ret = 0;
	double op_adj;
	double accel = 0;
	double dist;
	double obs_try = 0; //TRY_LEFT, TRY_RIGHT, NO_OBS
	int try_nb = 0,
	cant_go_to = -1;
	uint8_t pose_called_counter = 0;
	double obs_coef_x;
	double obs_accel_z;
	double dist_to_dest;
	double dist_to_dest_old;
	long int inaccessible_counter = 0;
	int coef_dist_inv_innaccessible;
	while ((ros::ok()) && (cant_go_to < 0)) {
	
		if (Odometry::pose_called) {
			pose_called_counter = 5;
			Odometry::pose_called = 0;
		} else {
			if (pose_called_counter > 0)
				pose_called_counter--;
		}
		
		if (Odometry::rot_called && (pose_called_counter > 0) && this->called_obs) {
			this->called_obs = 0;
			Odometry::rot_called = 0;
			
			if (in_range()) {
				msg.linear.x = 0;
				msg.angular.z = 0;
				accel = 0;
				is_moving.data = 0;
				cant_go_to = 0;
				moving.publish(is_moving);
				return cant_go_to;
			} else {
				is_moving.data = 1;
				moving.publish(is_moving);
				
				
				dist_to_dest_old = dist_to_dest;
				dist_to_dest = sqrt(((cmd_pose.x - Odometry::pose.x) * (cmd_pose.x - Odometry::pose.x)) + ((cmd_pose.y - Odometry::pose.y) * (cmd_pose.y - Odometry::pose.y)));
				
				coef_dist_inv_innaccessible = 101 - ((dist_to_dest < 100) ? dist_to_dest : 100);
				printf("coef too far : %d\n", coef_dist_inv_innaccessible);
				if (dist_to_dest >= dist_to_dest_old)
				{
					inaccessible_counter += coef_dist_inv_innaccessible;
				}
				else 
				{
					inaccessible_counter -= coef_dist_inv_innaccessible;
					if (inaccessible_counter <= -100) {
						inaccessible_counter = -100;
					}
				}
				if (inaccessible_counter > INNACCESSIBLE_COUNTER_MAX)
				{
					
					cant_go_to = 1;
				}
				
				printf("going too far : %ld\n", inaccessible_counter);
				
				
				if (((cmd_pose.x - Odometry::pose.x) < 0) && ((cmd_pose.y - Odometry::pose.y) > 0)) {
					op_adj = - (atan((cmd_pose.x - Odometry::pose.x)/(cmd_pose.y - Odometry::pose.y)) / 3.14) + 0.5;
					//ok
				} else if ((cmd_pose.x - Odometry::pose.x) < 0) {
					op_adj = - (atan((cmd_pose.x - Odometry::pose.x)/(cmd_pose.y - Odometry::pose.y)) / 3.14) + 1.5;
					
				} else if (((cmd_pose.x - Odometry::pose.x) > 0) && ((cmd_pose.y - Odometry::pose.y) > 0)) {
					op_adj = atan((cmd_pose.y - Odometry::pose.y)/(cmd_pose.x - Odometry::pose.x)) / 3.14;
					//ok
				} else {
					op_adj = (atan((cmd_pose.y - Odometry::pose.y)/(cmd_pose.x - Odometry::pose.x)) / 3.14) + 2;
					
				}
				
				if (op_adj > 1)
					op_adj -= 2;
				printf("is at x : %lf\t y : %lf\n", pose.x, pose.y);
				printf("going at x : %lf\t y : %lf\n", cmd_pose.x, cmd_pose.y);
				ret = modify_target_from_lidar(&obs_coef_x,
									&obs_accel_z,
									&obs_try,
									&try_nb,
									&op_adj);
									
				if (ret < 0) {
					cant_go_to = 1;
					//stop ?
				} else if (ret == 1) {
					
					msg.angular.z = op_adj;
				} else {
					msg.angular.z = op_adj - Odometry::rot; 
				}
				
				
				
				if (msg.angular.z > 1)
					msg.angular.z = msg.angular.z - 2;
				if (msg.angular.z < -1)
					msg.angular.z = msg.angular.z + 2;
					
				
				dist = sqrt(((cmd_pose.x - Odometry::pose.x) * (cmd_pose.x - Odometry::pose.x)) + ((cmd_pose.y - Odometry::pose.y) * (cmd_pose.y - Odometry::pose.y)));
				
				if ((accel < 0.1) && (dist > 1))
					accel = accel + 0.0005;
				
				msg.linear.x = ((accel * dist) / 2) * obs_coef_x;
				
				if (msg.linear.x >= 0.5)
					msg.linear.x = 0.5;
					
				msg.angular.z = msg.angular.z;
				
				if (msg.angular.z > 0.2)
				{
					msg.angular.z = 0.2;
				}
			}
			cmd_xy.publish(msg);
		} else {
			printf("at least one topic is not publishing : gps : %d, obs : %d, imu :%d\n", Odometry::pose_called, this->called_obs, Odometry::rot_called);
		}
		rate.sleep();
		ros::spinOnce();
	}
	return cant_go_to;
}

void Go_To::set_target(double x, double y) {
	this->cmd_pose.x = x;
	this->cmd_pose.y = y;
}
