#include "..\Public\state_stack.h"

/*
=====================================

STATE STACK

=====================================
*/

State::State(StateStack* stack)
	: _stack(stack)
{
}

StateStack::StateStack(void)
	: _states()
{
}

StateStack::~StateStack(void)
{
	clear();
}

bool StateStack::isEmpty(void) const
{
	return !_states.empty();
}

void StateStack::clear(void)
{
	for (unsigned int i = 0; i < _states.size(); i++)
	{
		delete _states.at(i);
		_states.erase(i + _states.begin());
	}
}