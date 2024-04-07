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

## Coord GPS node 



## Go To 



## Waste Labeling

### Publish

- Topic Name : Label/id
- Topic Type : std_msgs/String
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/String.html)


- Topic Name : Aspi/Status
- Topic Type : std_msgs::Bool 
[Documentation]()


## Detect 

### Publish

- Topic Name : /pif/waste/pos 
- Topic Type : geometry_msgs/Point 
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Point.html)

- Topic Name : /pif/waste/geometry
- Topic Type : geometry_msgs/QuaternionStamped 
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/QuaternionStamped.html)

### Subscribe 

- Topic Name :  /pif/moving
- Topic Type :  std_msgs/Bool
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)



