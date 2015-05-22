#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <string>
#include "TTTHud.h"
#include "GlobalVariables.h"

#define FONTSTYLE "../Orbitron/Orbitron-Regular.ttf"

HUD::HUD()
{
	HUDStartX = min(w, h);
	HUDWidth = max(w, h) - min(w, h);
	if (!font.loadFromFile(FONTSTYLE))
	{
		std::cout << "ERROR: Unable to load font " << FONTSTYLE << " into the TTTHud" << std::endl;
		Sleep(10000);
		exit(1);
	}
}

HUD::~HUD()
{

}

void HUD::DrawHUD()
{
	DrawDividerLine();
	DrawTurnText();
	DrawInstructions();
}

void HUD::DrawDividerLine()
{
	sf::Vector2f size(4, h);
	sf::RectangleShape line(size);
	line.setPosition(HUDStartX, 0);
	line.setFillColor(sf::Color(0, 0, 0));
	window.draw(line);
}

void HUD::DrawTurnText()
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(36);
	text.setPosition(HUDStartX + 15, 5);
	if (playerOnesTurn)
	{
		text.setString("X's turn");
		text.setColor(sf::Color(255, 0, 0));
	}
	else
	{
		text.setString("O's turn");
		text.setColor(sf::Color(0, 0, 255));
	}
	window.draw(text);
}

void HUD::DrawInstructions()
{
	//nothing here for now, since the instructions were crappy anyway
}

//This is probably obsolete given that I'm switching to a better design anyway
void HUD::DrawWinnerText()
{
	/*
	int x = min(w, h) / 2;
	int y = min(w, h) / 2;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(100);
	text.setPosition(x, y);
	*/
}
