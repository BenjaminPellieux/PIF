#!/usr/bin/env python
from flexbe_core import EventState, Logger


class PIF_CheckArrayState(EventState):
    '''
    Checks if the given condition is true and returns the corresponding outcome.
    This state can be used if the further control flow of the behavior depends on a simple condition.

    -- expected    string	    The value expected.

    >= input_value	object		Input to the predicate function.

    <= true 					Returned if all the values are set as expected.
    <= false 					Returned if not all the values are set as expected.
    '''

    def __init__(self, predicate):
        super(PIF_CheckArrayState, self).__init__(outcomes=['true', 'false'],
                                                  input_keys=['input_value'])
        self._predicate = predicate
        self._outcome = 'true'

    def execute(self, userdata):
        return self._outcome

    def on_enter(self, userdata):
        for value in userdata.input_value :
            try:
                if value != self._predicate:
                    self._outcome = 'false'
                    break
            except Exception as e:
                Logger.logwarn('Failed to execute condition function!\n%s' % str(e))
