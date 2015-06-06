#include "BlackHole.h"
#include "GlobalVariables.h"

#define BH BlackHole
#define strength -1.0
#define EventHorizon 5

BH::BlackHole()
{
	position = sf::Vector2f(static_cast<float>(w / 2), static_cast<float>(h / 2));
}

BH::BlackHole(float x, float y)
{
	position = sf::Vector2f(x, y);
}

BH::BlackHole(sf::Vector2f pos)
{
	position = pos;
}

BH::~BlackHole()
{
	delete stormblink;
}

void BH::Draw()
{
	/*
	sf::CircleShape ball;
	ball.setRadius(10);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(5, 5);
	ball.setPosition(position);
	window.draw(ball);
	*/
	stormblink->update(0, w / 2, h / 2);
}

sf::Vector2f BH::GetPosition()
{
	return position;
}

float BH::GetStrength()
{
	return strength;
}

float BH::GetEventHorizon()
{
	return EventHorizon;
}

void BH::LoadShader()
{
	stormblink = new StormBlink();
}
