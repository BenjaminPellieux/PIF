
#ROS lib
import rospy
from std_msgs.msg import String
from sensor_msgs.msg import NavSatFix
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3

# Python std lib
from pyproj import Transformer, CRS
import numpy as np
from dataclasses import dataclass

@dataclass
class Local_Pose():
	self.lat: float = 0
	self.lon: float = 0

class gps_transform():


	def __init__(self):

		# ROS 
		rospy.init_node('gps_transform', anonymous=True)
		rospy.Subscriber("/pif/gps", NavSatFix, self.callback)
		self.pub_gsp_convert = rospy.Publisher('/pif/gps_converted', Odometry, queue_size=10)
		self.rate = rospy.Rate(10) # 10hz


		self.robot_pose: Local_Pose = Local_Pose() 
		self.origin_pose: Local_Pose = Local_Pose()
		self.called: bool = False
		self.odom: Odometry = Odometry()
		self.__start__()
		

	def callback(self, NavSatFix)-> None:
		self.called = True
		self.robot_pose.lat = NavSatFix.latitude
		self.robot_pose.lon = NavSatFix.longitude


		# Fonction pour convertir de ECEF à ENU
	def ecef_to_enu(self, x, y, z, ref_alt = 0) -> tuple:
		# Transformer de géodésique (LLA) à ECEF pour obtenir les
		#coordonnées du point de référence
		transformer = Transformer.from_crs(CRS("EPSG:4326"), CRS("EPSG:4978"), always_xy=True)
		ref_x, ref_y, ref_z = transformer.transform(self.robot_pose.lon, self.robot_pose.lat, ref_alt)

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
		return tuple(enu)

	def __start__(self) -> None:
		
		for i in range(10):
			while not rospy.is_shutdown() and not self.called:
				pass
			self.called = False
			self.origin_pose.lat += self.robot_pose.lat
			self.origin_pose.lon += self.robot_pose.lon
			print(f"[DEBUG] origin get {i}")
		
		try:
			self.origin_pose.lat /= 10
			self.origin_pose.lon /= 10
		except ZeroDivisionError:
			print("[ERROR] Divition by zero")
			pass
		
		print(f"[LOG] origin found : {self.origin_pose.lat} {self.origin_pose.lon}")
		self.__run__()
	

	def __run__(self) -> None:

		while not rospy.is_shutdown():
			if self.called:
				print(f"[DEBUG] Here i am")
				self.called = False
				 # Altitude assumée à 0 pour simplifier

				# Transformer de géodésique (LLA) à ECEF pour obtenir les coordonnées
				# ECEF du robot
				transformer = Transformer.from_crs(CRS("EPSG:4326"), CRS("EPSG:4978"), always_xy=True)
				robot_x, robot_y, robot_z = transformer.transform(self.robot_pose.lon, self.robot_pose.lat)

				# Convertir les coordonnées ECEF du robot en coordonnées ENU par rapport
				# au point de référence
				self.odom.pose.pose.position.x, self.odom.pose.pose.position.y, _ = self.ecef_to_enu(robot_x, robot_y, robot_z)
				print(f"[LOG] Coordonnées ENU : {self.odom.pose.pose.position.x} {self.odom.pose.pose.position.y}")
				self.pub_gsp_convert.publish(self.odom)
				self.rate.sleep()

if __name__ == '__main__':
    try:
        gpn_convert = gps_transform()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass

