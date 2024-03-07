#!/usr/bin/env python
from flexbe_core import EventState
from flexbe_core.proxy import ProxyPublisher
from geometry_msgs.msg import Twist


class PIFMoveState(EventState):
	'''
	State to send move commands to jackal for PIF.

	-- topic	string	The topic on which should be published.

	>= linear 	float 	Linear value to move.
	>= angular	float	Angular value to move.

	<= done 			Command has been send.

	'''

	def __init__(self, topic):
		super(PIFMoveState, self).__init__(outcomes = ['done'],
									 	   input_keys=['linear', 'angular']
										   )
		self._topic = topic
		self._pub = ProxyPublisher({self._topic: Twist})

	def execute(self, userdata):
		return 'done'

	def on_enter(self, userdata):
		val = Twist()
		val.linear.x = userdata.linear
		val.angular.z = userdata.angular
		self._pub.publish(self._topic, val)
