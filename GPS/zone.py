import rospy
from sensor_msgs.msg import NavSatFix
from geometry_msgs.msg import PointStamped
from math import sqrt

class Zone:
    def __init__(self):
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
        rospy.loginfo("Coordonnées GPS : Latitude = %f, Longitude = %f", self.global_latitude, self.global_longitude)

    def is_inside_rectangle(self, A, B, C, D, P):
        # Vérifier si le point est à l'intérieur du rectangle ABCD
        min_x = min(A.x, B.x, C.x, D.x)
        max_x = max(A.x, B.x, C.x, D.x)
        min_y = min(A.y, B.y, C.y, D.y)
        max_y = max(A.y, B.y, C.y, D.y)

        if min_x <= P.x <= max_x and min_y <= P.y <= max_y:
            return True
        else:
            return False

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

def main():
    rospy.init_node('zone_node')
    zone = Zone()
    rospy.Subscriber('/NavSat/fix', NavSatFix, zone.gps_callback)
    rospy.Subscriber('/Area/Point', PointStamped, zone.zone_callback)
    rospy.spin()

if __name__ == '__main__':
    main()
