#include "pif_go_to.hpp"


Go_To::Go_To(){
	this->pose = (Local_Pose) {0.0, 0.0};
	this->cmd_pose = (Local_Pose) {0.0, 0.0};
	
	this->sub_gps = this->pos_xy.subscribe("/odometry/gps", 1000, &Go_To::callback_gps, this);
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

int Go_To::get_cmd_from_obs(double *coef_x, double *obs_try, int *try_nb, double *size_try, double *target_ang)
{
	if (this->called_obs) {
	
		printf("obs angle : %lf\n", this->obs_ang);
		printf("obs dist : %lf\n", this->obs_dist);
		this->called_obs = false;
		double tmp_dist = sqrt(((this->cmd_pose.x - this->pose.x) * (this->cmd_pose.x - this->pose.x)) \
							+ ((this->cmd_pose.y - this->pose.y) * (this->cmd_pose.y - this->pose.y)));
		if (this->obs_dist == 0) {
			//nothing
			*coef_x = 1;
		} else if (this->obs_dist < 1) { //if too close
			*coef_x = 0;//stop
		} else if (this->obs_dist < 2) {
			//if obstacle 
			
			if (*try_nb == NO_OBS) {
				*try_nb++;
				*size_try = tmp_dist + 10;
				if (this->obs_ang > 0) {
					*obs_try = TRY_RIGHT;
				} else {
					*obs_try = TRY_LEFT;
				}
			} 
				
			if (*try_nb) {
				*coef_x = this->obs_dist - 0.5;
				if (*size_try < tmp_dist) {
					*size_try = *size_try + 10;
					
					if (*try_nb == 2) 
						return -1;
					*try_nb++;
					*obs_try = *obs_try * (- 1);
					*coef_x = 0;
				}
				
				*target_ang += ((1 - (this->obs_dist - 1)) * (this->obs_ang + ((- *obs_try) / 2.0))) \
								 + ((this->obs_dist - 1) * *target_ang);
				printf("coef dist : %lf\nnew target : %lf\n", (this->obs_dist - 1), *target_ang);
				*coef_x = (1 - (this->obs_dist - 1)) + 0.01;
			}
		} else {
			*obs_try = 0;
			*try_nb = 0;
			*coef_x = 1;
		}
			
			
	}
	return 0;
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
    double size_try;
    	
	while (ros::ok())
	{
		sleep(0.5);
		if (this->called && this->gps_called) {
			this->gps_called = false;
			this->called = false;
			printf("[LOG] x : %lf\ny : %lf\nr_z : %lf\n", this->pose.x, this->pose.y, this->r_z);
			printf("[LOG] cmd x : %lf\ncmd y : %lf\n", this->cmd_pose.x, cmd_pose.y);
			if (this->in_range()) {
				msg.linear.x = 0;
				msg.angular.z = 0;
				accel = 0;
			} else {
				if (((this->cmd_pose.x - this->pose.x) < 0) && ((this->cmd_pose.y - this->pose.y) > 0)) {
					op_adj = - (atan((this->cmd_pose.x - this->pose.x) / (this->cmd_pose.y - this->pose.y)) / M_PI) + 0.5;
					//ok
				} else if ((this->cmd_pose.x - this->pose.x) < 0) {
					op_adj = - (atan((this->cmd_pose.x - this->pose.x) / (this->cmd_pose.y - this->pose.y)) / M_PI) + 1.5;
					
				} else if (((this->cmd_pose.x - this->pose.x) > 0) && ((this->cmd_pose.y - this->pose.y) > 0)) {
					op_adj = atan((this->cmd_pose.y - this->pose.y)/(this->cmd_pose.x - this->pose.x)) / M_PI;
					//ok
				} else {
					op_adj = (atan((this->cmd_pose.y - this->pose.y) / (this->cmd_pose.x - this->pose.x)) / M_PI) + 2;
					
				}
				if (get_cmd_from_obs(&obs_coef_x, &obs_try, &try_nb, &size_try, &op_adj) < 0) {
					cant_go_to = true;
					//stop ?
				}
				
				msg.angular.z = op_adj - this->r_z;
				
				if (msg.angular.z > 1)
					msg.angular.z = msg.angular.z - 2;
					
				dist = sqrt(((this->cmd_pose.x - this->pose.x) * (this->cmd_pose.x - this->pose.x)) \
						 + ((this->cmd_pose.y - this->pose.y) * (this->cmd_pose.y - this->pose.y)));
				
				if ((accel < 0.1) && (dist > 1))
					accel = accel + 0.001;
				
				msg.linear.x = ((accel * sqrt(((this->cmd_pose.x - this->pose.x) * (this->cmd_pose.x - this->pose.x)) \
							 + ((this->cmd_pose.y - this->pose.y) * (this->cmd_pose.y - this->pose.y)))) / 2) * obs_coef_x;
				
				if (msg.linear.x >= 1) 
					msg.linear.x = 1;
				
				msg.angular.z = msg.angular.z * 2;
				
				printf("[LOG] rov angular : %lf\n", this->r_z);
				printf("[LOG] point angle : %lf\n", op_adj);
				printf("[LOG] cmd angle : %lf\n", msg.angular.z);
				printf("[LOG] accel : %lf\n", accel);
				
			}
			this->cmd_xy.publish(msg);
		}
		ros::spinOnce();
	}
}

int main(int argc, char *argv[])
{

		
	ros::init(argc, argv, "pif_go_to_node");
	printf("trying to subscribe to /odometry/filtered and /pif_cmd...\n");
	printf("subscribed\n");
	Go_To pif_to_to = Go_To();
	pif_to_to.run();


	return 0;
}
