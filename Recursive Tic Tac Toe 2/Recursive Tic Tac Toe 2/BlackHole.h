#pragma once
#include <SFML/Graphics.hpp>
#include "StormBlink.h"

class BlackHole
{
public:
	BlackHole();
	BlackHole(float x, float y);
	BlackHole(sf::Vector2f pos);
	~BlackHole();

	void Draw();
	sf::Vector2f GetPosition();
	float GetStrength();
	float GetEventHorizon();

private:
	sf::Vector2f position;
	Effect* stormblink;
	int framesExisted; //used for the black hole pulsation

	void LoadShader();
};
