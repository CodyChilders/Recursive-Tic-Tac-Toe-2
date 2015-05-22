#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD();
	~HUD();
	void DrawHUD();
private:
	int HUDStartX;
	int HUDWidth;
	int edgeOffset;
	sf::Font font;
	
	void DrawDividerLine();
	void DrawTurnText();
	void DrawInstructions();
	void DrawWinnerText();
};