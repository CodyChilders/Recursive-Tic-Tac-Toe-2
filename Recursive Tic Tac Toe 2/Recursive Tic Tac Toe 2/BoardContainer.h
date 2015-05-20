#pragma once
#include "Board.h"

class BoardContainer : public Board
{
public:
	BoardContainer();
	BoardContainer(int xx, int yy, int ww, int hh, int recursionDepth);
	BoardContainer(BoardContainer* b);
	~BoardContainer();

	void ProcessMouseEvent() override;
	void Draw() override;

private:
	Board*** board;
	int depth;

	void CreateNewBoard();
	int SubGamesWon();
	void CheckForWin();
};
