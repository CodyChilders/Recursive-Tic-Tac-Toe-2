#include <iostream>
#include <exception>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"

#define and &&
#define or ||
#define not !

using namespace std;

Board::Board()
{
	//throw new std::exception("ERROR: can not create Board from an empty constructor.");
}

Board::Board(int xx, int yy, int ww, int hh)
{
	CreateNewBoard();
	x = xx;
	y = yy;
	w = ww;
	h = hh;
	movesPerformed = 0;
	winner = EMPTY;
}

Board::~Board()
{
	for (int i = 0; i < 3; i++)
	{
		delete board[i];
	}
	delete board;
}

void Board::ProcessMouseEvent()
{
	std::cout << "Board.ProcessMouseEvent() not yet implemented\n";
}

void Board::Draw()
{
	if (movesPerformed < 9)
	{
		DrawLines();
		DrawPieces();
	}
	else
	{
		DrawWinner();
	}
}

int Board::GetWinner()
{
	return winner;
}

void Board::DrawLines()
{
	std::cout << "Board.DrawLines() not yet implemented\n";
}

void Board::DrawWinner()
{
	if (winner == PLAYER1)
	{
		DrawX(x, y, w, h);
	}
	else if (winner == PLAYER2)
	{
		DrawO(x, y, w, h);
	}
	else
	{
		throw new std::exception("ERROR: winner declared as an invalid type.  This is a bug.");
	}
}

void Board::DrawX(int px, int py, int dx, int dy)
{
	std::cout << "Board.DrawX() not yet implemented\n";
}

void Board::DrawO(int px, int py, int dx, int dy)
{
	std::cout << "Board.DrawO() not yet implemented\n";
}

void Board::CreateNewBoard()
{
	//allocate the board
	board = new int*[3];
	for (int i = 0; i < 3; i++)
	{
		board[i] = new int[3];
		//empty it out just to be sure
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = EMPTY;
		}
	}
}

void Board::CheckForWin()
{
	//no need to check if there haven't been enough moves
	if (movesPerformed < 3)
		return;

	bool foundWin = false;
	for (int i = PLAYER1; i <= PLAYER2; i++)
	{
		//rows
		if (board[0][0] == i and board[0][1] == i and board[0][2] == i)
		{
			foundWin = true;
			goto Board_CheckForWin_SkipFurtherChecking;
		}
		if (board[1][0] == i and board[1][1] == i and board[1][2] == i)
		{
			foundWin = true;
			goto Board_CheckForWin_SkipFurtherChecking;
		}
		if (board[2][0] == i and board[2][1] == i and board[2][2] == i)
		{
			foundWin = true;
			goto Board_CheckForWin_SkipFurtherChecking;
		}
		//columns
		if (board[0][0] == i and board[1][0] == i and board[2][0] == i)
		{
			foundWin = true;
			goto Board_CheckForWin_SkipFurtherChecking;
		}
		if (board[0][1] == i and board[1][1] == i and board[2][1] == i)
		{
			foundWin = true;
			goto Board_CheckForWin_SkipFurtherChecking;
		}
		if (board[0][2] == i and board[1][2] == i and board[2][2] == i)
		{
			foundWin = true;
			goto Board_CheckForWin_SkipFurtherChecking;
		}
		//diagonals
		if (board[0][0] == i and board[1][1] == i and board[2][2] == i)
		{
			foundWin = true;
			goto Board_CheckForWin_SkipFurtherChecking;
		}
		if (board[2][0] == i and board[1][1] == i and board[0][2] == i)
		{
			foundWin = true;
			//no need for the goto since it goes to the right line anyway
		}
		//resolve the checks
Board_CheckForWin_SkipFurtherChecking:
		if (foundWin)
		{
			winner = i;
			movesPerformed = 9; //setting this to 9 closes off the board to other moves
			return;
		}
	}
}

void Board::DrawPieces()
{
	//Draw the x's and o's
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int piece = board[i][j];
			if (piece == EMPTY)
			{
				continue; //no need to draw anything for this, move on to the next one
			}
			else
			{
				//Determine the size and location of the token
				int px = x + i * w / 3;
				int py = y + j * h / 3;
				int dx = w / 3;
				int dy = h / 3;
				//draw the correct shape
				if (piece == PLAYER1)
				{
					DrawX(px, py, dx, dy);
				}
				else if (piece == PLAYER2)
				{
					DrawO(px, py, dx, dy);
				}
				else
				{
					throw new std::exception("ERROR: invalid piece in the game board");
				}
			}
		}
	}
}
