#pragma once

/*Standard Library*/
#include <vector>

/*
=====================================

STATE STACK

=====================================
*/

class StateStack;

class State
{
public:
	State						(StateStack* stack);

	virtual void draw			(void) = 0;
	virtual void handle			(float delta) = 0;
	virtual void update			(float delta) = 0;
protected:
	StateStack*		_stack;
};

class StateStack
{
public:
	StateStack					(void);
	virtual ~StateStack			(void);

	virtual void push			(State* state) = 0;
	virtual void pop			(void) = 0;
	virtual State* peek			(void) = 0;
	virtual void swap			(State* state) = 0;

	bool isEmpty				(void) const;
	void clear					(void);
protected:
	std::vector<State*> _states;
};