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

#define MS_PER_FRAME 17

int w = 1150, h = 950;

typedef BoardContainer Game;

Game* game;
bool playerOnesTurn = true;
bool freshBoard = true;
sf::RenderWindow window(sf::VideoMode(w, h), "Recursive Tic-Tac-Toe 2");
sf::Color backgroundColor = sf::Color(255, 255, 255);
int gameRecursionDepth = 2;

void Setup()
{
	game = new BoardContainer(0, 0, min(w, h), min(w, h), gameRecursionDepth);
}

void Draw()
{
	while (window.isOpen())
	{
		//for framerate limiting
		unsigned int timeAtStart = time(nullptr);
		//drawing, event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return;
			}
		}

		window.clear(backgroundColor);
		game->Draw();
		window.display();
		//for framerate limiting
		unsigned int timeNow = time(nullptr);
		unsigned int delta = timeNow - timeAtStart;
		Sleep(MS_PER_FRAME - delta);
	}
}

void Teardown()
{
	window.close();
	delete game;
	exit(0);
}

int main()
{
	Setup();
	Draw();
	Teardown();
}
