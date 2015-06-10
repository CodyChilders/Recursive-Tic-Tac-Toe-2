#include <SFML/Graphics.hpp>
#include "BoardContainer.h"
#include "GlobalVariables.h"
#include "Shooter.h"

#define BC BoardContainer
#define and &&
#define or ||
#define not !

BC::BoardContainer()
{
	
}

BC::BoardContainer(int xx, int yy, int ww, int hh, int recursionDepth)
{
	if (recursionDepth <= 0)
	{
		throw new std::exception("ERROR: can't create a board container with a negative depth.  It will result in an infinite construction and eat all memory");
	}
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
	//Delete the board instances
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			delete board[i][j];
		}
	}
	//delete the inner arrays
	for (int i = 0; i < 3; i++)
	{
		delete [] board[i];
	}
	//delete the outer array
	delete [] board;
}

void BC::ProcessMouseEvent()
{
	//printf("BoardContainer.ProcessMouseEvent not yet implemented\n");
	//if it isn't in the bounds of this square or it is full, no need to do anything
	if (mouseX < x || mouseY < y || mouseX > x + w || mouseY > y + h || movesPerformed == 9)
	{
		return;
	}
	//see how many of the sub-games are complete
	int subGamesCompleteBeforeTurn = SubGamesWon();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			bool preUpdate = playerOnesTurn;
			board[i][j]->ProcessMouseEvent();
			if (preUpdate != playerOnesTurn) //this detects when one of the lower boards changed the state of the board
			{
				if (SubGamesWon() != subGamesCompleteBeforeTurn)
					movesPerformed++;
				CheckForWin();
				return;
			}
		}
	}
}

void BC::Draw()
{
	//if the game is still ongoing
	if (movesPerformed < 9)
	{
		DrawLines();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				board[i][j]->Draw();
			}
		}
	}
	else //If the game has been completed
	{
		DrawWinner();
	}
}

void BC::CreateNewBoard()
{
	//allocate the board array
	board = new Board**[3];
	for (int i = 0; i < 3; i++)
	{
		board[i] = new Board*[3];
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
				board[i][j] = new Board(a, b, c, d);
			}
			else
			{
				board[i][j] = new BoardContainer(a, b, c, d, depth - 1);
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
			if (board[i][j]->GetWinner() != EMPTY)
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
		if (board[0][0]->GetWinner() == i and board[0][1]->GetWinner() == i and board[0][2]->GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[1][0]->GetWinner() == i and board[1][1]->GetWinner() == i and board[1][2]->GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[2][0]->GetWinner() == i and board[2][1]->GetWinner() == i and board[2][2]->GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}

		//columns
		if (board[0][0]->GetWinner() == i and board[1][0]->GetWinner() == i and board[2][0]->GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[0][1]->GetWinner() == i and board[1][1]->GetWinner() == i and board[2][1]->GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[0][2]->GetWinner() == i and board[1][2]->GetWinner() == i and board[2][2]->GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}

		//diagonals
		if (board[0][0]->GetWinner() == i and board[1][1]->GetWinner() == i and board[2][2]->GetWinner() == i)
		{
			foundWin = true;
			goto BoardContainer_CheckForWin_SkipFurtherChecking;
		}
		if (board[2][0]->GetWinner() == i and board[1][1]->GetWinner() == i and board[0][2]->GetWinner() == i)
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
		/*
		//TODO switch to a non-solved game mode in here to decide who wins.
		CreateNewBoard();
		movesPerformed = 0;
		*/
		contestedBoard = this;
		states->PushState(new Shooter());
		return;
	}
}
