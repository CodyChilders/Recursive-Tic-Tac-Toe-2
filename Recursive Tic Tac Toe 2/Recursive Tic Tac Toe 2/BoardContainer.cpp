#include <SFML/Graphics.hpp>
#include "BoardContainer.h"

#define BC BoardContainer

BC::BoardContainer()
{
	//throw new std::exception("ERROR: BoardContainer can not be created with the default constructor");
}

BC::BoardContainer(int xx, int yy, int ww, int hh, int recursionDepth)
{
	x = xx;
	y = yy;
	w = ww;
	h = hh;
	depth = recursionDepth;
	movesPerformed = 0;
	CreateNewBoard();
}

BC::~BoardContainer()
{
	for (int i = 0; i < 3; i++)
	{
		delete board[i];
	}
	delete board;
}

void BC::ProcessMouseEvent()
{

}

void BC::Draw()
{

}

void BC::CreateNewBoard()
{
	//allocate the board array
	board = new Board*[3];
	for (int i = 0; i < 3; i++)
	{
		board[i] = new Board[3];
	}
	//allocate the correct type into the array
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//determine the x, y, width, and height values
			int a = x + i * w / 3;
			int b = y + j * h / 3;
			int c = w / 3;
			int d = h / 3;
			//allocate the correct type into the array
			if (depth == 1)
			{
				board[i][j] = Board(a, b, c, d);
			}
			else
			{
				board[i][j] = BoardContainer(a, b, c, d, depth - 1);
			}
		}
	}
}

int BC::SubGamesWon()
{
	int gamesWon = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j].GetWinner() != EMPTY)
			{
				gamesWon++;
			}
		}
	}
	return gamesWon;
}

void BC::CheckForWin()
{
	//slightly optimize things for early game
	if (movesPerformed < 3)
	{
		return;
	}
	bool foundWin = false;
	//check the 8 ways, 1 by 1 in a loop for each player
	for (int i = PLAYER1; i <= PLAYER2; i++)
	{
		//Rows
		if (board[0][0].GetWinner() == i && board[0][1].GetWinner() == i && board[0][2].GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[1][0].GetWinner() == i && board[1][1].GetWinner() == i && board[1][2].GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[2][0].GetWinner() == i && board[2][1].GetWinner() == i && board[2][2].GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}

		//columns
		if (board[0][0].GetWinner() == i && board[1][0].GetWinner() == i && board[2][0].GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[0][1].GetWinner() == i && board[1][1].GetWinner() == i && board[2][1].GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[0][2].GetWinner() == i && board[1][2].GetWinner() == i && board[2][2].GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}

		//diagonals
		if (board[0][0].GetWinner() == i && board[1][1].GetWinner() == i && board[2][2].GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[2][0].GetWinner() == i && board[1][1].GetWinner() == i && board[0][2].GetWinner() == i)
		{
			foundWin = true;
			//the goto is unnecessary because the check is the next line anyway
		}
BoardContainer_CheckForWin_SkipFurtherChecking:
		//finally, resolve if a win was found
		if (foundWin)
		{
			winner = i;
			movesPerformed = 9; //Setting this to full closes off the board to other use
			return;
		}
	}
	//if it exits the loop but there were 9 moves performed, it is a cats-game.  Reset
	if (movesPerformed == 9)
	{
		//TODO switch to a non-solved game mode in here to decide who wins.
		CreateNewBoard();
		movesPerformed = 0;
		return;
	}
}
