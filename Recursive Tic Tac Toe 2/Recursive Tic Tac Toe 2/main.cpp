#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "GlobalVariables.h"
#include "Board.h"
#include "BoardContainer.h"

int w = 1150, h = 950;

typedef BoardContainer* Game;

Game game;
bool playerOnesTurn = true;
bool freshBoard = true;
sf::RenderWindow window(sf::VideoMode(w, h), "Recursive Tic-Tac-Toe 2");
sf::Color backgroundColor = sf::Color(255, 255, 255);

void Setup()
{
	game = new BoardContainer();
}

void Draw()
{
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				//delete game;
				window.close();
			}
		}

		window.clear();
		//window.draw(shape);
		game->Draw();
		window.display();
	}
}

int main()
{
	Setup();
	Draw();
}
