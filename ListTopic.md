# Introcution 

Ce document a  pour but de presenter l'ensemble des topic utiliser par notre solution


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
- Topic Name : /Mode/Status  
- Topic Type : std_msgs/Bool
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)


### Subscribe

Position Odometrique de Wall-E
- Topic Name : /odometry/filtered
- Topic Type : nav_msgs/Odometry Message
[Documentation](http://docs.ros.org/en/noetic/api/nav_msgs/html/msg/Odometry.html)


Position GPS de Wall-E
- Topic Name : /navsat/fix
- Topic Type : sensor_msgs/NavSatFix
[Documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/NavSatFix.html)


- Topic Name : 
- Topic Type : 
[Documentation]()

### Coord GPS node 



## path_finding

### odometry

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

- Topic Name : Waste/Pos 
- Topic Type : geometry_msgs/Point 
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Point.html)

- Topic Name : Waste/Geometry
- Topic Type : geometry_msgs/QuaternionStamped 
[Documentation](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/QuaternionStamped.html)

#### Subscribe 

- Topic Name :  /pif/moving
- Topic Type :  std_msgs/Bool
[Documentation](http://docs.ros.org/en/melodic/api/std_msgs/html/msg/Bool.html)


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
