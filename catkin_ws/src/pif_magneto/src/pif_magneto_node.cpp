#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <errno.h> 
#include <termios.h> 
#include <unistd.h> 


int main(int argc, char **argv){
	ros::init(argc, argv, "path_finding_node");

    ros::NodeHandle nh;
    
    nav_msgs::Odometry nav;
        ros::Publisher pub_magn = nh.advertise<nav_msgs::Odometry>("/pif/magn", 100);
    struct termios tty;
    memset(&tty, 0, sizeof tty);
	int serial_port = -1;
	int i = 0;
	int tty_ok = 0;
	int tty_is_good_tty = 0;
	
    while (ros::ok() && (i < 5)) {
	while ((i < 5) && (serial_port < 0)) {
		switch (i) {
			case 0:
    			serial_port = open("/dev/ttyACM0", O_RDWR);
			break;
			case 1:
    			serial_port = open("/dev/ttyACM1", O_RDWR);
			break;
			case 2:
    			serial_port = open("/dev/ttyACM2", O_RDWR);
			break;
			case 3:
    			serial_port = open("/dev/ttyACM3", O_RDWR);
			break;
			case 4:
    			serial_port = open("/dev/ttyACM4", O_RDWR);
			break;
			case 5:
    			serial_port = open("/dev/ttyACM5", O_RDWR);
			break;
		}
		i++;
	}

    	// Check for errors
    	if (serial_port < 0) {
        	printf("Error %i from open: %s\n", errno, strerror(errno));
    	}
	
        	// Read in existing settings, and handle any error
    	if(tcgetattr(serial_port, &tty) != 0) {
        	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    	}
	
	
	
		tty.c_cflag &= ~CRTSCTS;    
		tty.c_cflag |= (CLOCAL | CREAD);                   
		tty.c_iflag |= (IGNPAR | IGNCR);                  
		tty.c_iflag &= ~(IXON | IXOFF | IXANY);          
		tty.c_oflag &= ~OPOST;
		
		tty.c_cflag &= ~CSIZE;            
		tty.c_cflag |= CS8;              
		tty.c_cflag &= ~PARENB;         
		tty.c_iflag &= ~INPCK;         
		tty.c_iflag &= ~(ICRNL|IGNCR);
		tty.c_cflag &= ~CSTOPB;      
		tty.c_iflag |= INPCK;       
		tty.c_cc[VTIME] = 0.001;  //  1s=10   0.1s=1 *
		tty.c_cc[VMIN] = 0;
    	// Set in/out baud rate to be 9600
    	cfsetispeed(&tty, B9600);
    	cfsetospeed(&tty, B9600);
	
    	// Save tty settings, also checking for error
    	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        	printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    	}
	
    	// Allocate memory for read buffer, set size according to your needs
    	char read_buf [8];
    	memset(&read_buf, '\0', sizeof(read_buf));
		tty_ok = 0;
    	while(ros::ok() && (tty_ok >= 0)){
        		int n = read(serial_port, &read_buf, 8);
        		std::cout << read_buf;
        		if ((n == 8) && (read_buf[0] == 'x'))
        		{
          		if (tty_ok == 0)
        				tty_is_good_tty++;
        			nav.pose.pose.orientation.z = atof(&read_buf[1]);
        			pub_magn.publish(nav);
        			ros::spinOnce();
        		} else {
        		if (tty_ok == 0)
        				tty_is_good_tty--;
        		}
        		
        		if (tty_ok == 0)
        		{
        			if(tty_is_good_tty < -100) {
        				tty_ok = -1;
        			} else if (tty_is_good_tty > 10) {
        				tty_ok = 1;
        			}
        		}
    	}
    }

    return 0;
}
