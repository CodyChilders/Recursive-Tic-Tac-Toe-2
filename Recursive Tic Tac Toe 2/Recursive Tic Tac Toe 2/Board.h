#pragma once

class Board
{
public:
	typedef enum BoardStates {EMPTY = 0, PLAYER1 = 1, PLAYER2 = 2};
	const sf::Color xColor = sf::Color::Red;
	const sf::Color oColor = sf::Color::Blue;

	Board();
	Board(int px, int py, int dx, int dy);
	Board(Board* b);
	~Board();

	virtual void ProcessMouseEvent();
	virtual void Draw();
	int GetWinner();

protected:
	int x, //x coordinate of the top left corner
		y, //y coordinate of the top left corner
		w, //width  of this board
		h; //height of this board
	int winner;
	int movesPerformed;

	void DrawLines();
	void DrawWinner();
	void DrawX(int px, int py, int dx, int dy);
	void DrawO(int px, int py, int dx, int dy);

private:
	int board[3][3];
	void CreateNewBoard();
	void CheckForWin();
	void DrawPieces();
};
