#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GlobalVariables.h"
#include "Board.h"
#include "BoardContainer.h"

int w = 1150, h = 950;

typedef BoardContainer Game;

Game* game;
int mouseX = 0,
	mouseY = 0;
bool playerOnesTurn = true;
bool freshBoard = true;
sf::RenderWindow window(sf::VideoMode(w, h), "Recursive Tic-Tac-Toe 2");
sf::Color backgroundColor = sf::Color(255, 255, 255);
int gameRecursionDepth = 1;
int msPerFrame = 17;

void Setup()
{
	game = new BoardContainer(0, 0, min(w, h), min(w, h), gameRecursionDepth);
}

void Draw()
{
	while (window.isOpen())
	{
		//for framerate limiting
		time_t timeAtStart = time(nullptr);
		//drawing, event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			//window closing
			if (event.type == sf::Event::Closed)
			{
				return;
			}
			//mouse being clicked
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition();
				mouseX = mousePosition.x;
				mouseY = mousePosition.y;
				game->ProcessMouseEvent();
			}
		}

		window.clear(backgroundColor);
		game->Draw();
		window.display();
		//for framerate limiting
		time_t timeNow = time(nullptr);
		time_t delta = timeNow - timeAtStart;
		Sleep(static_cast<unsigned int>(msPerFrame - delta));
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
