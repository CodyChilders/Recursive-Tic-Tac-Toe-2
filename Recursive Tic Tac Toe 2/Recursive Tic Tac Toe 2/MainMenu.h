#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"

class MainMenu : public State
{
public:
	MainMenu();
	~MainMenu();
	void Draw() override;
	void ProcessMouseEvent() override;
private:
	sf::RectangleShape startButton;
	sf::Font font;

	void DrawTitle();
	void DrawButtons();
};