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

<<<<<<< HEAD
## Coord GPS node 
=======
### Coord GPS node
>>>>>>> 43b07d9ef14c71cde6d596fa66b995aa76f525b6



## path_finding

### odometry

<<<<<<< HEAD

## Waste Labeling

### Publish

- Topic Name : Label/id
- Topic Type : std_msgs/String
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/String.html)


- Topic Name : Aspi/Status
- Topic Type : std_msgs::Bool 
[Documentation]()


## Vision Detect 

### Publish

- Topic Name : /pif/waste/pos 
- Topic Type : geometry_msgs/Point 
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Point.html)

- Topic Name : /pif/waste/geometry
- Topic Type : geometry_msgs/QuaternionStamped 
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/QuaternionStamped.html)
=======
#### Subscribe 

Position actuelle sous X et Y
- Topic Name :  /pif/gps_converted
- Topic Type :  nav_msgs/Odometry
[Documentation](https://docs.ros.org/en/noetic/api/nav_msgs/html/msg/Odometry.html)

Rotation actuelle absolue en (rad / PI - 1)
- Topic Name :  /imu/data
- Topic Type :  sensor_msgs/Imu
[Documentation](https://docs.ros.org/en/noetic/api/sensor_msgs/html/msg/Imu.html)


### go_to

#### Publish

- Topic Name : /cmd_vel
- Topic Type : geometry_msgs/Twist
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Twist.html)

- Topic Name : /pif/moving
- Topic Type : std_msgs/Bool
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)

#### Subscribe 

- Topic Name :  /obstacle_marker
- Topic Type :  visualization_msgs/Marker
[Documentation](http://docs.ros.org/en/noetic/api/visualization_msgs/html/msg/Marker.html)


### define_area

#### Subscribe 

Zone selectionne
- Topic Name :  /area/polygon
- Topic Type :  geometry_msgs/PolygonStamped
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)


### check_waste

#### Publish

Envoi de commande de rotation
- Topic Name : /cmd_vel
- Topic Type : geometry_msgs/Twist
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Twist.html)

#### Subscribe

Angle du déchet par raport au robot
- Topic Name :  /Waste/Geometry
- Topic Type :  geometry_msgs/QuaternionStamped
[Documentation](https://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/QuaternionStamped.html)

Dechet detecte et sa position
- Topic Name :  /Label/id
- Topic Type :  path_finding/PoseWasteStamped
[Documentation](
    | Header header
    | path_finding/PoseWaste data => | string waste
                                     | geometry_msgs/Point center (https://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Point.html)
)



## Coord GPS node 

### Publish

position gps du robot (rtk)
- Topic Name : /pif/gps
- Topic Type : sensor_msgs/NavSatFix
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)



## Gps reset 

### Publish

- Topic Name : /pif/origin
- Topic Type : sensor_msgs/NavSatFix
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)
>>>>>>> 43b07d9ef14c71cde6d596fa66b995aa76f525b6

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
