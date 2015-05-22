#include <cstdlib>
#include <Windows.h>
#include "TicTacToe.h"
#include "GlobalVariables.h"

#define TTT TicTacToe
#define gameRecursionDepth 2

TTT::TicTacToe()
{
	game = new BoardContainer(0, 0, min(w, h), min(w, h), gameRecursionDepth);
	hud = new HUD();
}

TTT::~TicTacToe()
{
	delete game;
	delete hud;
}

void TTT::Draw()
{
	game->Draw();
	hud->DrawHUD();
}

void TTT::ProcessMouseEvent()
{
	game->ProcessMouseEvent();
}
