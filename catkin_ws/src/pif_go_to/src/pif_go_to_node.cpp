#include "pif_go_to.hpp"


Go_To::Go_To(){
	this->pose = (Local_Pose) {0.0, 0.0};
	this->cmd_pose = (Local_Pose) {0.0, 0.0};
	
	this->sub_gps = this->pos_xy.subscribe("/pif/gps_converted", 1000, &Go_To::callback_gps, this);
	this->sub_odom = this->pos_xy.subscribe("/odometry/filtered", 1000, &Go_To::callback_odom, this);
	this->sub_cmd = this->pos_xy.subscribe("/pif_cmd", 1000, &Go_To::callback_cmd, this);
	this->sub_laser = this->pos_xy.subscribe("/obstacle_marker", 1000, &Go_To::callback_obs, this);
	this->cmd_xy = this->pos_xy.advertise<geometry_msgs::Twist>("/cmd_vel", 1);


}
void Go_To::callback_obs(const visualization_msgs::Marker::ConstPtr &mark)
{
	if (! this->called_obs)
		this->called_obs = true;
		
	if (mark->pose.orientation.z > 0) {
		this->obs_ang = mark->pose.orientation.z;
	} else {
		this->obs_ang = mark->pose.orientation.z + 2; 
	}
	this->obs_dist = mark->scale.x;
}


void Go_To::callback_gps(const nav_msgs::Odometry::ConstPtr &nav)
{
	if (! this->gps_called)
		this->gps_called = true;
		
	this->pose.x = nav->pose.pose.position.x;
	this->pose.y = nav->pose.pose.position.y;
}

void Go_To::callback_odom(const nav_msgs::Odometry::ConstPtr &odometry)
{
	if (odometry->pose.pose.orientation.z > 0) {
		this->r_z = odometry->pose.pose.orientation.z;
	} else {
		this->r_z = odometry->pose.pose.orientation.z + 2; 
	}
	
	if (!this->called)
		this->called = true;
}

void Go_To::callback_cmd(const geometry_msgs::Pose::ConstPtr &cmd)
{
	this->cmd_pose.x = cmd->position.x;
	this->cmd_pose.y = cmd->position.y;
}

bool Go_To::in_range() {
	
	if ((this->pose.x < this->cmd_pose.x + RANGE_GOOD_ENOUGH)
		&& (this->pose.x > this->cmd_pose.x - RANGE_GOOD_ENOUGH)
		&& (this->pose.y < this->cmd_pose.y + RANGE_GOOD_ENOUGH)
		&& (this->pose.y > this->cmd_pose.y - RANGE_GOOD_ENOUGH)) {
		return 1;
	} else {
		return 0;
	}
}

int Go_To::get_cmd_from_obs(double *coef_x,
	double *accel_z,
	double *obs_try,
	int *try_nb,
	double *target_ang,
	uint8_t dist_at_begin)
{
	int ret = 0;
	double angle_to_add;

	
		if (called_obs) {
		
			called_obs = 0;
			
			if (obs_dist == 0) {
				//nothing
				*obs_try = 0;
				*try_nb = 0;
				*coef_x = 1;
			} else if (obs_dist < 1) { //if too close
				*coef_x = 0;//stop
			} else if (obs_dist < 3) {
				//if obstacle 
				
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
					/*if (dist_at_begin < sqrt(((cmd_x - x) * (cmd_x - x)) + ((cmd_y - y) * (cmd_y - y)))) {
						dist_at_begin = dist_at_begin + 5;
						
						if (*try_nb == 2) 
							return -1;
						*try_nb++;
						*obs_try = *obs_try * (- 1);
						*coef_x = 0;
					}*/
					
					*target_ang = ((1 - ((obs_dist - 1) / 2)) * (obs_ang - 1)) ;
					if (*target_ang > 1) 
						*target_ang - 2;
					if (*target_ang < -1) 
						*target_ang + 2;
					*coef_x = ((obs_dist - 1) / 2);
					//if (*coef_x < 0.3)
					//	*coef_x = 0.3;
					
					
					/*if ((*try_nb > 0) ? (*target_ang > 0) && (*target_ang < 0.5) : (*target_ang < 0) && (*target_ang > (- 0.5))) {
						*coef_x = 1;
					} else {
						target_to_avoid_colision = obs_ang + *obs_try;
						*target_ang = angle_to_add + (((obs_dist - 1) / 2) * *target_ang);
						*coef_x = ((obs_dist - 1) / 2);
					}*/
					
					
				}
			} else {
				*obs_try = 0;
				*try_nb = 0;
				*coef_x = 1;
			}
			
			
		} else {
			*coef_x = 0;
			printf("No laser topic\n");
		}
		
	return ret;
}

void Go_To::run(){

    geometry_msgs::Twist msg;
    	
    	double op_adj;
    	double accel = 0;
    	double dist;
    	double obs_try = 0; //TRY_LEFT, TRY_RIGHT, NO_OBS
    	int try_nb = 0;
    	
    	double obs_coef_x;
    	double obs_accel_z;
    	double dist_to_dest;
    	uint8_t start_move = 0;
    	
	while (ros::ok())
	{
		sleep(0.5);
		if (called && gps_called) {
			gps_called = 0;
			called = 0;
			
			if (in_range()) {
				msg.linear.x = 0;
				msg.angular.z = 0;
				accel = 0;
				start_move = 1;
			} else {
				if (start_move)
					dist_to_dest = sqrt(((cmd_pose.x - pose.x) * (cmd_pose.x - pose.x)) + ((cmd_pose.y - pose.y) * (cmd_pose.y - pose.y))) + 5;
				start_move = 0;
				
				if (((cmd_pose.x - pose.x) < 0) && ((cmd_pose.y - pose.y) > 0)) {
					op_adj = - (atan((cmd_pose.x - pose.x)/(cmd_pose.y - pose.y)) / 3.14) + 0.5;
					//ok
				} else if ((cmd_pose.x - pose.x) < 0) {
					op_adj = - (atan((cmd_pose.x - pose.x)/(cmd_pose.y - pose.y)) / 3.14) + 1.5;
					
				} else if (((cmd_pose.x - pose.x) > 0) && ((cmd_pose.y - pose.y) > 0)) {
					op_adj = atan((cmd_pose.y - pose.y)/(cmd_pose.x - pose.x)) / 3.14;
					//ok
				} else {
					op_adj = (atan((cmd_pose.y - pose.y)/(cmd_pose.x - pose.x)) / 3.14) + 2;
					
				}
				
				if (op_adj > 1)
					op_adj -= 2;
				printf("point angle : %lf\n", op_adj);
				if (get_cmd_from_obs(&obs_coef_x,
					&obs_accel_z,
					&obs_try,
					&try_nb,
					&op_adj,
					dist_to_dest) < 0) {
					cant_go_to = 1;
					exit(0);
					//stop ?
				}
				
				
				msg.angular.z = op_adj - (r_z - 1);
				
				if (msg.angular.z > 1)
					msg.angular.z = msg.angular.z - 2;
				if (msg.angular.z < -1)
					msg.angular.z = msg.angular.z + 2;
					
				
				dist = sqrt(((cmd_pose.x - pose.x) * (cmd_pose.x - pose.x)) + ((cmd_pose.y - pose.y) * (cmd_pose.y - pose.y)));
				
				if ((accel < 0.1) && (dist > 1))
					accel = accel + 0.0005;
				
				
				
				
				msg.linear.x = ((accel * sqrt(((cmd_pose.x - pose.x) * (cmd_pose.x - pose.x)) + ((cmd_pose.y - pose.y) * (cmd_pose.y - pose.y)))) / 2) * obs_coef_x;
				
				if (msg.linear.x >= 0.5) 
					msg.linear.x = 0.5;
					
				
			}
			cmd_xy.publish(msg);
		}
		ros::spinOnce();
	}

}

int main(int argc, char *argv[])
{

		
	ros::init(argc, argv, "pif_go_to_node");
	printf("trying to subscribe to /odometry/filtered and /pif_cmd...\n");
	Go_To pif_to_to = Go_To();
	pif_to_to.run();


	return 0;
}
