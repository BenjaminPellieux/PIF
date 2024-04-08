# Introcution 

Ce document à pour but de présenter l'ensemble des topics utilisés par notre solution


## Serveur WEB

### Publish

Envoi les point de la zone GPS 
- Topic Name : /Area/Point
- Topic Type : sensor_msgs/NavSatFix
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)


Envoi de commande de deplacement
- Topic Name : /jackal_velocity_controller/cmd_vel
- Topic Type : geometry_msgs/Twist
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Twist.html)

Controle manuel ou automatique
- Topic Name : /pif/web/controle 
- Topic Type : std_msgs/Bool
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)


### Subscribe

Position Odometrique de Wall-E
- Topic Name : /odometry/filtered
- Topic Type : nav_msgs/Odometry Message
[Documentation](http://docs.ros.org/en/noetic/api/nav_msgs/html/msg/Odometry.html)


Position GPS de Wall-E
- Topic Name : /pif/gps
- Topic Type : sensor_msgs/NavSatFix
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)


- Topic Name : 
- Topic Type : 
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)

### Coord GPS node



## path_finding

### odometry


## Waste Labeling

### Publish

- Topic Name : /pif/hard/label
- Topic Type : std_msgs/String
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/String.html)


- Topic Name : /pif/hard/aspi
- Topic Type : std_msgs/Bool 
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)


## Vision Detect 

### Publish

- Topic Name : /pif/waste/pos 
- Topic Type : geometry_msgs/Point 
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Point.html)

- Topic Name : /pif/waste/geometry
- Topic Type : geometry_msgs/QuaternionStamped 
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/QuaternionStamped.html)

### Subscribe 





## Gps reset origin 


### Subscribe 

- Topic Name : argument[1] (/pif/gps or /navsat/fix in simu)
- Topic Type : sensor_msgs/NavSatFix
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)

- Topic Name : /pif/reset_origin
- Topic Type : std_msgs/Bool
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)



## Gps transform

### Publish

- Topic Name : argument[2] (/pif/gps_converted for go_to but can be used for zone_select)
- Topic Type : std_msgs/Point
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)

### Subscribe 

- Topic Name : /pif/origin
- Topic Type : sensor_msgs/NavSatFix
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)

- Topic Name : argument[1] (/pif/gps or /navsat/fix in simu)
- Topic Type : sensor_msgs/NavSatFix
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)



## scan detect obstacle (lidar)

### Publish

- Topic Name :  /obstacle_marker
- Topic Type :  visualization_msgs/Marker
[Documentation](http://docs.ros.org/en/noetic/api/visualization_msgs/html/msg/Marker.html)

### Subscribe 

- Topic Name : argument[1] (/scan or /front/scan in simu)
- Topic Type : sensor_msgs/LaserScan
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/LaserScan.html)
