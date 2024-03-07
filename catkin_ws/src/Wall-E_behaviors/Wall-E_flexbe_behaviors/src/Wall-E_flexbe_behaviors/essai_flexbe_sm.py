#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from flexbe_states.calculation_state import CalculationState
from flexbe_states.check_condition_state import CheckConditionState
from flexbe_states.wait_state import WaitState
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Mon Mar 04 2024
@author: Erwan MAWART
'''
class essai_flexbeSM(Behavior):
	'''
	c'est une présentation.
	'''


	def __init__(self):
		super(essai_flexbeSM, self).__init__()
		self.name = 'essai_flexbe'

		# parameters of this behavior

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		# x:514 y:116, x:365 y:216
		_state_machine = OperatableStateMachine(outcomes=['finished', 'failed'])
		_state_machine.userdata.const = 1

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]


		with _state_machine:
			# x:30 y:40
			OperatableStateMachine.add('state 1',
										CalculationState(calculation=lambda input_value: input_value * 2),
										transitions={'done': 'state 2'},
										autonomy={'done': Autonomy.Off},
										remapping={'input_value': 'const', 'output_value': 'output_value'})

			# x:171 y:76
			OperatableStateMachine.add('state 2',
										WaitState(wait_time=2),
										transitions={'done': 'state 3'},
										autonomy={'done': Autonomy.Off})

			# x:311 y:104
			OperatableStateMachine.add('state 3',
										CheckConditionState(predicate=lambda input_value:  input_value > 2),
										transitions={'true': 'finished', 'false': 'failed'},
										autonomy={'true': Autonomy.Off, 'false': Autonomy.Off},
										remapping={'input_value': 'output_value'})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
