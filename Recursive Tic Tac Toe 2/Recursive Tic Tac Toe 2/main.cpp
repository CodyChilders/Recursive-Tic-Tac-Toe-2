#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "GlobalVariables.h"
#include "StateMachine.h"
#include "Shooter.h"

int w = 1150, h = 950;

StateMachine* states;
AudioManager* audio;

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
	//TicTacToe* ttt = new TicTacToe();
	//states = new StateMachine(ttt);
	MainMenu* mm = new MainMenu();
	states = new StateMachine(mm);
	//Shooter* s = new Shooter();
	//states = new StateMachine(s);

	audio = new AudioManager();
}

void Draw()
{
	while (window.isOpen())
	{
		//for framerate limiting
		time_t timeAtStart = time(nullptr);
		//Update the mouse information so everything else can find it
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		mouseX = mousePosition.x;
		mouseY = mousePosition.y;
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
				states->ProcessMouseEvent();
			}
		}
		states->Update();
		window.clear(backgroundColor);
		states->Draw();
		window.display();
		//for framerate limiting
		time_t timeNow = time(nullptr);
		time_t delta = timeNow - timeAtStart;
		int sleepTime = static_cast<int>(msPerFrame - delta);
		//printf("Slept thread for %d ms\n", sleepTime);
		if (sleepTime > 0)
			Sleep(sleepTime);
	}
}

void Teardown()
{
	window.close();
	delete states;
	exit(0);
}

int main()
{
	Setup();
	Draw();
	Teardown();
}
