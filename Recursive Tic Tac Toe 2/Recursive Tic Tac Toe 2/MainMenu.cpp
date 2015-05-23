#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "MainMenu.h"
#include "TicTacToe.h"
#include "GlobalVariables.h"

#define MM MainMenu
#define ButtonWidth 500
#define ButtonHeight 200
#define FONTSTYLE "../Orbitron/Orbitron-Regular.ttf"

MM::MainMenu()
{
	//set up the start game button
	sf::Vector2f sb = sf::Vector2f(ButtonWidth, ButtonHeight);
	startButton = sf::RectangleShape(sb);
	startButton.setFillColor(sf::Color::Yellow);
	startButton.setOrigin(sf::Vector2f(ButtonWidth / 2, ButtonHeight / 2));
	startButton.setOutlineColor(sf::Color::Black);
	startButton.setPosition(w / 2, h / 2);
	//load the font
	if (!font.loadFromFile(FONTSTYLE))
	{
		std::cout << "ERROR: Unable to load font " << FONTSTYLE << " into the TTTHud" << std::endl;
		Sleep(10000);
		exit(1);
	}
}

MM::~MainMenu()
{

}

void MM::Draw()
{
	window.clear(sf::Color::Black);
	DrawTitle();
	DrawButtons();
}

void MM::ProcessMouseEvent()
{
	if (startButton.getGlobalBounds().contains(mouseX, mouseY))
	{
		audio->PlayButton();
		states->PushState(new TicTacToe());
	}
}

void MM::DrawTitle()
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(75);
	text.setString("Recursive Tic Tac Toe 2");
	text.setColor(sf::Color::Red);

	sf::FloatRect bounds = text.getGlobalBounds();
	int x = w / 2 - bounds.width / 2;
	int y = 50;
	text.setPosition(x, y);
	window.draw(text);
}

void MM::DrawButtons()
{
	window.draw(startButton);
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(45);
	text.setString("Start Game");
	text.setColor(sf::Color::Black);

	sf::FloatRect textBounds = text.getGlobalBounds();
	sf::FloatRect buttonBounds = startButton.getGlobalBounds();
	int x = (buttonBounds.left + buttonBounds.width  / 2) - textBounds.width  / 2;
	int y = (buttonBounds.top  + buttonBounds.height / 2) - textBounds.height / 2;
	text.setPosition(x, y);
	window.draw(text);
}

