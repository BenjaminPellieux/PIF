#!/usr/bin/env python
# ROS lib
import sys
import rospy
from sys import argv
from std_msgs.msg import String
from sensor_msgs.msg import NavSatFix
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3

# Python std lib
from pyproj import Transformer, CRS
import numpy as np
from lib_pos import *

class gps_transform():

    def __init__(self):

        # ROS 
        rospy.init_node('gps_transform', anonymous=True)
        rospy.Subscriber(argv[1], NavSatFix, self.callback_transform)
        rospy.Subscriber('/pif/origin', NavSatFix, self.callback_origin)
        self.pub_gps_convert = rospy.Publisher(argv[2], Point, queue_size=10)
        self.rate = rospy.Rate(10) # 10hz

        self.robot_pose: Local_Pose = Local_Pose() 
        self.origin_pose: Local_Pose = Local_Pose()
        self.called_transform: bool = False
        self.called_origin: bool = False
        self.odom: Point = Point()
        self.__run__()

    def callback_transform(self, data)-> None:
        self.called_transform = True
        self.header = data.header
        self.robot_pose.lat = data.latitude
        self.robot_pose.lon = data.longitude
        
    def callback_origin(self, data)-> None:
        self.called_origin = True
        self.origin_pose.lat = data.latitude
        self.origin_pose.lon = data.longitude

    # Fonction pour convertir de ECEF à ENU
    def ecef_to_enu(self, x, y, z, ref_alt = 0) -> tuple:
        # Transformer de géodésique (LLA) à ECEF pour obtenir les
        # coordonnées du point de référence
        transformer = Transformer.from_crs(CRS("EPSG:4326"), CRS("EPSG:4978"), always_xy=True)
        #ref_x, ref_y, ref_z = transformer.transform(self.robot_pose.lon, self.robot_pose.lat, ref_alt)
        ref_x, ref_y, ref_z = transformer.transform(self.origin_pose.lon, self.origin_pose.lat, ref_alt)

        # Calculer les différences entre les coordonnées ECEF
        dx, dy, dz = x - ref_x, y - ref_y, z - ref_z

        # Calculer les coordonnées ENU
        a = np.radians(self.robot_pose.lat)
        b = np.radians(self.robot_pose.lon)
        m = np.array([
            [-np.sin(b),              np.cos(b),             0],
            [-np.sin(a)*np.cos(b),  -np.sin(a)*np.sin(b),  np.cos(a)],
            [ np.cos(a)*np.cos(b),   np.cos(a)*np.sin(b),  np.sin(a)]
        ])
        enu = np.dot(m, [dx, dy, dz])
        return tuple(enu.tolist())

   

    def __run__(self) -> None:
        while not rospy.is_shutdown():
            if self.called_transform and self.called_origin:
                self.called_transform = False
                # Altitude assumée à 0 pour simplifier

                # Transformer de géodésique (LLA) à ECEF pour obtenir les coordonnées
                # ECEF du robot
                transformer = Transformer.from_crs(CRS("EPSG:4326"), CRS("EPSG:4978"), always_xy=True)
                robot_x, robot_y, robot_z = transformer.transform(self.robot_pose.lon, self.robot_pose.lat, 0)

                # Convertir les coordonnées ECEF du robot en coordonnées ENU par rapport
                # au point de référence
                self.odom.x, self.odom.y, _ = self.ecef_to_enu(robot_x, robot_y, robot_z)
                print(f"[LOG] Coordonnées ENU : {self.odom.x} {self.odom.y}")
                self.odom.header = self.header
                self.pub_gps_convert.publish(self.odom)
                self.rate.sleep()

if __name__ == '__main__':
    try:
        gps_convert: gps_transform = gps_transform()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
