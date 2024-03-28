#!/usr/bin/env python

import rospy
from sensor_msgs.msg import NavSatFix
from geometry_msgs.msg import PointStamped
from std_msgs.msg import Bool

class ZoneChecker:
    def __init__(self):
        rospy.init_node('zone_checker')
        rospy.Subscriber('/navsat/fix', NavSatFix, self.gps_callback)
        rospy.Subscriber('/Area/Point', PointStamped, self.zone_callback)
        self.in_zone_pub = rospy.Publisher('/in_zone', Bool, queue_size=10)
        self.global_latitude = 0.0
        self.global_longitude = 0.0
        self.P1 = None
        self.P2 = None
        self.P3 = None
        self.P4 = None

    def gps_callback(self, msg):
        # Callback appelée lors de la réception de messages GPS
        self.global_latitude = msg.latitude
        self.global_longitude = msg.longitude
        self.check_zone()

    def zone_callback(self, msg):
        point = msg.point
        if msg.header.frame_id == "P1":
            self.P1 = (point.x, point.y)
        elif msg.header.frame_id == "P2":
            self.P2 = (point.x, point.y)
        elif msg.header.frame_id == "P3":
            self.P3 = (point.x, point.y)
        elif msg.header.frame_id == "P4":
            self.P4 = (point.x, point.y)
        self.check_zone()

    def is_inside_rectangle(self, A, B, C, D, P):
        # Vérifier si le point est à l'intérieur du rectangle ABCD
        min_x = min(A.x, B.x, C.x, D.x)
        max_x = max(A.x, B.x, C.x, D.x)
        min_y = min(A.y, B.y, C.y, D.y)
        max_y = max(A.y, B.y, C.y, D.y)
        return min_x <= P.x <= max_x and min_y <= P.y <= max_y

    def check_zone(self):
        if self.P1 and self.P2 and self.P3 and self.P4:
            current_point = PointStamped()
            current_point.point.x = self.global_latitude
            current_point.point.y = self.global_longitude
            if self.is_inside_rectangle(self.P1, self.P2, self.P3, self.P4, current_point.point):
                self.in_zone_pub.publish(Bool(True))
            else:
                self.in_zone_pub.publish(Bool(False))

if __name__ == '__main__':
    try:
        zone_checker = ZoneChecker()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
