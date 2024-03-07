#!/usr/bin/env python
# -*- coding: utf-8 -*-
###########################################################
#               WARNING: Generated code!                  #
#              **************************                 #
# Manual changes may get lost if file is generated again. #
# Only code inside the [MANUAL] tags will be kept.        #
###########################################################

from flexbe_core import Behavior, Autonomy, OperatableStateMachine, ConcurrencyContainer, PriorityContainer, Logger
from flexbe_states.log_state import LogState
from flexbe_states.wait_state import WaitState
from tutorial_flexbe_states.example_state2 import ExampleState2
from tutorial_flexbe_states.pierre_state import PierreState
from tutorial_flexbe_states.subscriber_state_position import SubscriberStatePosition
# Additional imports can be added inside the following tags
# [MANUAL_IMPORT]

# [/MANUAL_IMPORT]


'''
Created on Fri Nov 05 2021
@author: P. Blazevic
'''
class Premier_testSM(Behavior):
	'''
	Ceci est mon premier test
	'''


	def __init__(self):
		super(Premier_testSM, self).__init__()
		self.name = 'Premier_test'

		# parameters of this behavior
		self.add_parameter('waiting_time', 1)

		# references to used behaviors

		# Additional initialization code can be added inside the following tags
		# [MANUAL_INIT]
		
		# [/MANUAL_INIT]

		# Behavior comments:



	def create(self):
		hello = "Hello World"
		# x:30 y:275
		_state_machine = OperatableStateMachine(outcomes=['finished'])

		# Additional creation code can be added inside the following tags
		# [MANUAL_CREATE]
		
		# [/MANUAL_CREATE]


		with _state_machine:
			# x:214 y:53
			OperatableStateMachine.add('wait_state',
										WaitState(wait_time=5),
										transitions={'done': 'Avant'},
										autonomy={'done': Autonomy.Off})

			# x:399 y:58
			OperatableStateMachine.add('Avant',
										LogState(text="Avant", severity=Logger.REPORT_HINT),
										transitions={'done': 'test'},
										autonomy={'done': Autonomy.Off})

			# x:500 y:396
			OperatableStateMachine.add('Place_bleu',
										PierreState(x=500, y=-300),
										transitions={'done': 'Apres'},
										autonomy={'done': Autonomy.Off})

			# x:773 y:280
			OperatableStateMachine.add('Place_rouge',
										PierreState(x=500, y=300),
										transitions={'done': 'home2'},
										autonomy={'done': Autonomy.Off})

			# x:771 y:110
			OperatableStateMachine.add('Receive',
										SubscriberStatePosition(topic="/position", blocking=True, clear=True),
										transitions={'received': 'Place_rouge', 'unavailable': 'Receive'},
										autonomy={'received': Autonomy.Off, 'unavailable': Autonomy.Off},
										remapping={'message': 'message'})

			# x:773 y:365
			OperatableStateMachine.add('home2',
										ExampleState2(target_time=1),
										transitions={'done': 'Place_bleu'},
										autonomy={'done': Autonomy.Off})

			# x:154 y:296
			OperatableStateMachine.add('print_message',
										LogState(text="FIN", severity=Logger.REPORT_HINT),
										transitions={'done': 'finished'},
										autonomy={'done': Autonomy.Off})

			# x:627 y:48
			OperatableStateMachine.add('test',
										ExampleState2(target_time=1),
										transitions={'done': 'Receive'},
										autonomy={'done': Autonomy.Off})

			# x:343 y:294
			OperatableStateMachine.add('Apres',
										LogState(text="Après", severity=Logger.REPORT_HINT),
										transitions={'done': 'print_message'},
										autonomy={'done': Autonomy.Off})


		return _state_machine


	# Private functions can be added inside the following tags
	# [MANUAL_FUNC]
	
	# [/MANUAL_FUNC]
