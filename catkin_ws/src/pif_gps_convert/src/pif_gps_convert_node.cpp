#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <sensor_msgs/NavSatStatus.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/Odometry.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h> 
#include <cstring>

#ifndef ACCEPT_USE_OF_DEPRECATED_PROJ_API_H
#define ACCEPT_USE_OF_DEPRECATED_PROJ_API_H 1
#endif

#define IP_ADDR_GPS_DIFF	"192.168.131.81"
#define PORT_GPS_DIFF		5600

int main(int argc, char *argv[])
{
	
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	sensor_msgs::NavSatFix pos;
	//nav_msgs::Odometry posxy;
	
	ros::init(argc, argv, "gps_convert_node");
	
	ros::NodeHandle gps_xy;

	ros::Publisher gps_pub = gps_xy.advertise<sensor_msgs::NavSatFix>("/pif/gps", 1000);
	//ros::Publisher gps_pub_xy = gps_xy.advertise<nav_msgs::Odometry>("/pif/xy", 1000);
	
	char buffer[256];

    
	portno = PORT_GPS_DIFF;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("ERROR opening socket\n");
		exit(-1);
	}
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		printf("ERROR, no such host\n");
		exit(-1);
	}
	printf("server found\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(portno);
	printf("trying to connect...\n");
	while (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) { 
		printf("ERROR connecting, retrying...\n");
	}

	printf("connected\n");
	
	while (ros::ok()) {
		n = write(sockfd, buffer, strlen(buffer));
		if (n < 0) {
			printf("ERROR writing to socket\n");
			//exit(-1);
			sleep(1);
		}
		
		bzero(buffer,256);
		
		n = read(sockfd, buffer, 255);
		if (n < 0) {
			printf("ERROR reading from socket\n");
			//exit(-1);
			sleep(1);
		} else {
			printf("buffer : %s\n", buffer);
			pos.latitude = atof(&buffer[24]);
			pos.longitude = atof(&buffer[38]);
			pos.altitude = 0.0633;
			printf("lat : %lf\nlon : %lf\n", pos.latitude, pos.longitude);

			//posxy.pose.pose.position.x = x;
			//posxy.pose.pose.position.y = y;

			//gps_pub_xy.publish(posxy);
			gps_pub.publish(pos);
			ros::spinOnce();
		}
		
		
	}
	


	return 0;
}
