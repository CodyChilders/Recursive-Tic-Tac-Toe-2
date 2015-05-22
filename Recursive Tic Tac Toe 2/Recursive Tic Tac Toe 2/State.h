#pragma once

class State
{
public:
	State();
	~State();
	virtual void Update();
	virtual void Draw();
	virtual void ProcessMouseEvent();
	virtual void ProcessKeyboardEvent();
	virtual void ProcessControllerEvent();
};
