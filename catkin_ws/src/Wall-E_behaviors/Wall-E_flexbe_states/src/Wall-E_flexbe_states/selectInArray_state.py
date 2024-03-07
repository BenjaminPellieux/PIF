#!/usr/bin/env python
from flexbe_core import EventState


class selectInArrayState(EventState):
	'''
	State to send move commands to jackal for PIF.

	>= array 	object 	Array that content the value.
	>= value	int 	Value to select in the array.

	=> output_value		string	Value returned.

	<= done 			Command has been send.

	'''

	def __init__(self):
		super(selectInArrayState, self).__init__(outcomes = ['done'],
                                                 input_keys=['array', 'value'],
				         output_keys=['output_value']
                                                )

	def execute(self, userdata):
		return 'done'

	def on_enter(self, userdata):
		userdata.output_value = userdata.array[userdata.value]
