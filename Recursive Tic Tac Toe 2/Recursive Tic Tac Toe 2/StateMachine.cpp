#include <stack>
#include <exception>
#include <iostream>
#include "StateMachine.h"
#include "State.h"

StateMachine::StateMachine(State* initial)
{
	states.push(initial);
}

StateMachine::~StateMachine()
{
	while (!states.empty())
	{
		State* top = states.top();
		states.pop();
		delete top;
	}
}

void StateMachine::Update()
{
	try
	{
		states.top()->Update();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

void StateMachine::Draw()
{
	try
	{
		states.top()->Draw();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

void StateMachine::PushState(State* newState)
{
	states.push(newState);
}

void StateMachine::PopState()
{
	if (states.empty() || states.size() == 1)
	{
		throw new std::exception("ERROR: requested to pop the last state in the stack");
	}
	State* poppedState = states.top();
	states.pop();
	delete poppedState;
}

void StateMachine::PopStates(int num)
{
	if (num < 0)
	{
		throw new std::exception("ERROR: can not pop a negative number of states off the stack");
	}
	for (int i = 0; i < num; i++)
	{
		PopState();
	}
}

void StateMachine::ProcessMouseEvent()
{
	try
	{
		states.top()->ProcessMouseEvent();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

void StateMachine::ProcessKeyboardEvent()
{
	try
	{
		states.top()->ProcessKeyboardEvent();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

void StateMachine::ProcessControllerEvent()
{
	try
	{
		states.top()->ProcessControllerEvent();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

State* StateMachine::GetCurrentState()
{
	return states.top();
}
