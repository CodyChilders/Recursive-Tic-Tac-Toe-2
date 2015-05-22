#pragma once
#include "State.h"
#include "BoardContainer.h"
#include "TTTHud.h"

class TicTacToe : public State
{
public:
	TicTacToe();
	~TicTacToe();
	void Update() override;
	void Draw() override;
	void ProcessMouseEvent() override;

private:
	typedef BoardContainer Game;
	Game* game;
	HUD* hud;
};
