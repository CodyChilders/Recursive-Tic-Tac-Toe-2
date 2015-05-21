#include <iostream>
#include <exception>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "GlobalVariables.h"

#define and &&
#define or ||
#define not !

using namespace std;

Board::Board()
{
	
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

Board::Board(Board* b)
{
	CreateNewBoard();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->board[i][j] = b->board[i][j];
		}
	}
	this->x = b->x;
	this->y = b->y;
	this->w = b->w;
	this->h = b->h;
	this->movesPerformed = b->movesPerformed;
	this->winner = b->winner;
}

Board::~Board()
{
	
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
	//the rectangle defining the verticle lines
	sf::Vector2f vertLinesSize(lineThickness, h - 2 * distanceFromEdges);
	sf::RectangleShape vertLine(vertLinesSize);
	vertLine.setFillColor(lineColor);
	vertLine.setOutlineColor(lineColor);
	//set the position of each and draw it
	vertLine.setPosition(x + w / 3, y + distanceFromEdges);
	window.draw(vertLine);
	vertLine.setPosition(x + w * 2 / 3, y + distanceFromEdges);
	window.draw(vertLine);
	//draw the horozontal lines
	sf::Vector2f horzLinesSize(w - 2 * distanceFromEdges, lineThickness);
	sf::RectangleShape horzLine(horzLinesSize);
	horzLine.setFillColor(lineColor);
	horzLine.setOutlineColor(lineColor);
	//set the position of each and draw it
	horzLine.setPosition(x + distanceFromEdges, y + h / 3);
	window.draw(horzLine);
	horzLine.setPosition(x + distanceFromEdges, y + h * 2 / 3);
	window.draw(horzLine);
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
	sf::Vector2f size(dx, dy / 3);
	sf::RectangleShape tl2br(size); //top left to bottom right bar
	sf::RectangleShape tr2bl(size); //top right to bottom left bar
	//set the origin to the middle of the shape
	tl2br.setOrigin(size.x / 2, size.y / 2);
	tr2bl.setOrigin(size.x / 2, size.y / 2);
	//set the colors
	tl2br.setFillColor(xColor);
	tr2bl.setFillColor(xColor);
	//set the rotations
	tl2br.setRotation(45);
	tr2bl.setRotation(-45);
	//position
	tl2br.setPosition(px + dx / 2, py + dy / 2);
	tr2bl.setPosition(px + dx / 2, py + dy / 2);
	//draw
	window.draw(tl2br);
	window.draw(tr2bl);
}

void Board::DrawO(int px, int py, int dx, int dy)
{
	sf::CircleShape shape(dx / 2);
	shape.setFillColor(oColor);
	sf::Vector2f pos(px, py);
	shape.setPosition(pos);
	window.draw(shape);
}

void Board::CreateNewBoard()
{
	//empty it out just to be sure
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = EMPTY;//(i + j) % 2 + 1;//PLAYER1;//EMPTY;
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
