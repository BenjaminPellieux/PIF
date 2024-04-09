#!/usr/bin/env python
# ROS lib

import rospy
from sys import argv
from std_msgs.msg import String
from std_msgs.msg import Bool
from sensor_msgs.msg import NavSatFix
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3
from pyproj import Transformer, CRS
from dataclasses import dataclass

@dataclass
class Local_Pose():
    lat: float = 0
    lon: float = 0



class gps_reset_origin():

    def __init__(self):

        # ROS 
        rospy.init_node('gps_reset_origin', anonymous=True)
        rospy.Subscriber(argv[1], NavSatFix, self.callback_gps)
        rospy.Subscriber('/pif/reset_origin', Bool, self.callback_reset)
        self.pub_gps_convert = rospy.Publisher('/pif/origin', NavSatFix, queue_size=10)
        self.rate = rospy.Rate(1) # 1hz

        self.robot_pose: Local_Pose = Local_Pose() 
        self.called_gps: bool = False
        self.called_reset: bool = False
        self.origin: NavSatFix = NavSatFix()
        self.reset: Bool = Bool()
        self.get_origin()
        self.__run__()



    def callback_gps(self, data)-> None:
        self.called_gps = True
        self.robot_pose.lat = data.latitude
        self.robot_pose.lon = data.longitude
        
    def callback_reset(self, data)-> None:
        self.called_reset = True
        self.reset = data
    

    def get_origin(self) -> None:
        i = 0
        self.origin.latitude = 0
        self.origin.longitude = 0
        while i < 10 and not rospy.is_shutdown():
            while not self.called_gps:
                pass
            self.called_gps = False
            self.origin.latitude += self.robot_pose.lat
            self.origin.longitude += self.robot_pose.lon
            print(f"[DEBUG] origin get {i}")
            i += 1
        
        try:
            self.origin.latitude /= 10
            self.origin.longitude /= 10
        except ZeroDivisionError:
            print("[ERROR] Division by zero")
        
        print(f"[LOG] origin found : {self.origin.latitude} {self.origin.longitude}")


    def __run__(self) -> None:
        while not rospy.is_shutdown():
            if self.called_reset:
                self.called_reset = False
                if self.reset:
                    self.get_origin()
                
            self.pub_gps_convert.publish(self.origin)
            self.rate.sleep()



if __name__ == '__main__':
    try:
        gps_convert = gps_reset_origin()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
