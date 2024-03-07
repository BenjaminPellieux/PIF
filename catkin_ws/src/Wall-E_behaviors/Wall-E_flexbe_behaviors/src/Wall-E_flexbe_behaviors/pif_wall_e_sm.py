#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from Wall-E_flexbe_behaviors.pif_spin_sm import PIF_SpinSM
from Wall-E_flexbe_states.PIF_CheckArray_state import PIF_CheckArrayState
from Wall-E_flexbe_states.PIF_move_state import PIFMoveState
from Wall-E_flexbe_states.PIF_updateGrid_state import PIFUpdateGridState
from flexbe_states.wait_state import WaitState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Wed Mar 06 2024
@author: Erwan MAWART
'''
class PIF_WallESM(Behavior):
	'''
	Projet InterFilière : Wall-E, le robot ramasseur de déchet.
	'''


	def __init__(self):
		super(PIF_WallESM, self).__init__()
		self.name = 'PIF_Wall-E'

		# parameters of this behavior

		# references to used behaviors
		self.add_behavior(PIF_SpinSM, 'PIF_Spin')

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		topic_cmd_vel = "/cmd_vel"
		setTile = "done"
		topic_detectTrash = "/vision/detectTrash"
		# x:150 y:277, x:968 y:38
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'])
		_state_machine.userdata.linear = 1.0
		_state_machine.userdata.angular = 25.0

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]

		# x:30 y:453, x:130 y:453
		_sm_get_trash_0 = OperatableStateMachine(outcomes=['failed', 'finished'], input_keys=['direction'])

		with _sm_get_trash_0:
			# x:30 y:40
			OperatableStateMachine.add('wait',
										WaitState(wait_time=0.1),
										transitions={'done': 'failed'},
										autonomy={'done': Autonomy.Off})


		# x:30 y:453, x:130 y:453
		_sm_set_origin_1 = OperatableStateMachine(outcomes=['finished', 'failed'])

		with _sm_set_origin_1:
			# x:30 y:40
			OperatableStateMachine.add('wait',
										WaitState(wait_time=0.1),
										transitions={'done': 'failed'},
										autonomy={'done': Autonomy.Off})


		# x:30 y:453, x:130 y:453
		_sm_create_grid_2 = OperatableStateMachine(outcomes=['finished', 'failed'], output_keys=['grid'])

		with _sm_create_grid_2:
			# x:30 y:40
			OperatableStateMachine.add('wait',
										WaitState(wait_time=0.1),
										transitions={'done': 'failed'},
										autonomy={'done': Autonomy.Off})


		# x:30 y:453, x:130 y:453
		_sm_choose_next_tile_3 = OperatableStateMachine(outcomes=['finished', 'failed'], output_keys=['area'])

		with _sm_choose_next_tile_3:
			# x:118 y:62
			OperatableStateMachine.add('wait',
										WaitState(wait_time=0.1),
										transitions={'done': 'failed'},
										autonomy={'done': Autonomy.Off})



		with _state_machine:
			# x:30 y:40
			OperatableStateMachine.add('Create grid',
										_sm_create_grid_2,
										transitions={'finished': 'Set origin', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'grid': 'grid'})

			# x:359 y:147
			OperatableStateMachine.add('Choose next tile',
										_sm_choose_next_tile_3,
										transitions={'finished': 'Go to middle', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'area': 'area'})

			# x:541 y:198
			OperatableStateMachine.add('Go to middle',
										PIFMoveState(topic=topic_cmd_vel),
										transitions={'done': 'PIF_Spin'},
										autonomy={'done': Autonomy.Off},
										remapping={'linear': 'linear', 'angular': 'angular'})

			# x:632 y:288
			OperatableStateMachine.add('PIF_Spin',
										self.use_behavior(PIF_SpinSM, 'PIF_Spin',
											parameters={'topic_detectTrash': topic_detectTrash, 'topic_cmd_vel': topic_cmd_vel}),
										transitions={'clear': 'upgrade tile', 'detected': 'get trash', 'failed': 'failed'},
										autonomy={'clear': Autonomy.Inherit, 'detected': Autonomy.Inherit, 'failed': Autonomy.Inherit},
										remapping={'direction': 'direction'})

			# x:186 y:94
			OperatableStateMachine.add('Set origin',
										_sm_set_origin_1,
										transitions={'finished': 'Choose next tile', 'failed': 'failed'},
										autonomy={'finished': Autonomy.Inherit, 'failed': Autonomy.Inherit})

			# x:885 y:234
			OperatableStateMachine.add('get trash',
										_sm_get_trash_0,
										transitions={'failed': 'failed', 'finished': 'Go to middle'},
										autonomy={'failed': Autonomy.Inherit, 'finished': Autonomy.Inherit},
										remapping={'direction': 'direction'})

			# x:451 y:344
			OperatableStateMachine.add('upgrade tile',
										PIFUpdateGridState(value=setTile),
										transitions={'done': 'Check unclean tiles left'},
										autonomy={'done': Autonomy.Off},
										remapping={'grid': 'grid', 'area': 'area', 'new_grid': 'new_grid'})

			# x:261 y:252
			OperatableStateMachine.add('Check unclean tiles left',
										PIF_CheckArrayState(predicate=setTile),
										transitions={'true': 'Choose next tile', 'false': 'finished'},
										autonomy={'true': Autonomy.Off, 'false': Autonomy.Off},
										remapping={'input_value': 'grid'})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
