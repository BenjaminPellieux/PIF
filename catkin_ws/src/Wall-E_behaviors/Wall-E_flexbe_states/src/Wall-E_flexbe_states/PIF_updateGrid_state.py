#!/usr/bin/env python
from flexbe_core import EventState


class PIFUpdateGridState(EventState):
	'''
	State to change value in grid for PIF.

	-- value	string	The new area's value

	>= grid		string 	Grid of clean and unclean areas.
	>= areaPosX		int		Current area coordonates in X.
	>= areaPosY		int		Current area coordonates in Y.

	=> new_grid		string	Grid of clean and unclean areas with modification.

	<= done 			Command has been send.

	'''

	def __init__(self, value):
		super(PIFUpdateGridState, self).__init__(outcomes = ['done'],
												input_keys=['grid', 'area'],
												output_keys=['new_grid']
												)
		self._value = value

	def execute(self, userdata):
		return 'done'

	def on_enter(self, userdata):
		userdata.grid[userdata.areaPosY][userdata.areaPosX] = self._value
		userdata.new_grid = userdata.grid
