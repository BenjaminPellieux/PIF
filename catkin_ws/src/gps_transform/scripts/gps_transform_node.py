
import rospy
from std_msgs.msg import String
from sensor_msgs.msg import NavSatFix
from pyproj import Transformer, CRS
import numpy as np
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3

lat:float = 0 
lon:float = 0
called:bool = False

def callback(NavSatFix):
	global lat
	global lon
	global called 
	called = True
	lat = NavSatFix.latitude
	lon = NavSatFix.longitude
	
# Fonction pour convertir de ECEF à ENU
def ecef_to_enu(x, y, z, ref_lat, ref_lon, ref_alt):
     # Transformer de géodésique (LLA) à ECEF pour obtenir les
	#coordonnées du point de référence
     transformer = Transformer.from_crs(CRS("EPSG:4326"), CRS("EPSG:4978"), always_xy=True)
     ref_x, ref_y, ref_z = transformer.transform(ref_lon, ref_lat, ref_alt)

     # Calculer les différences entre les coordonnées ECEF
     dx, dy, dz = x - ref_x, y - ref_y, z - ref_z

     # Calculer les coordonnées ENU
     a = np.radians(ref_lat)
     b = np.radians(ref_lon)
     m = np.array([
         [-np.sin(b),              np.cos(b),             0],
         [-np.sin(a)*np.cos(b),  -np.sin(a)*np.sin(b),  np.cos(a)],
         [ np.cos(a)*np.cos(b),   np.cos(a)*np.sin(b),  np.sin(a)]
     ])
     enu = np.dot(m, [dx, dy, dz])
     return tuple(enu)


odom = Odometry()
#ros publisher
rospy.init_node('gps_transform', anonymous=True)
pub = rospy.Publisher('/pif/gps_converted', Odometry, queue_size=10)
rospy.Subscriber("/pif/gps", NavSatFix, callback)
rate = rospy.Rate(10) # 10hz

#get origin position (0, 0)
origin_lat = 0
origin_lon = 0
for i in range(10):
	while not rospy.is_shutdown() and not called:
		pass
	called = False
	origin_lat += lat
	origin_lon += lon
	print(f"origin get {i}")
origin_lat /= 10
origin_lon /= 10

print(f"origin found : {origin_lat} {origin_lon}")

while not rospy.is_shutdown():
	if called == True:
		print(f"Here i am")
		called = False
		alt = 0  # Altitude assumée à 0 pour simplifier

		# Transformer de géodésique (LLA) à ECEF pour obtenir les coordonnées
		# ECEF du robot
		transformer = Transformer.from_crs(CRS("EPSG:4326"), CRS("EPSG:4978"), always_xy=True)
		robot_x, robot_y, robot_z = transformer.transform(lon, lat, alt)

		# Convertir les coordonnées ECEF du robot en coordonnées ENU par rapport
		# au point de référence
		odom.pose.pose.position.x, odom.pose.pose.position.y, _ = ecef_to_enu(robot_x, robot_y, robot_z, origin_lat, origin_lon, alt)
		print(f"Coordonnées ENU : {odom.pose.pose.position.x} {odom.pose.pose.position.y}")
		pub.publish(odom)
		rate.sleep()
