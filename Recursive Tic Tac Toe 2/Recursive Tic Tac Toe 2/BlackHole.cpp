#include "BlackHole.h"
#include "GlobalVariables.h"

#define BH BlackHole
#define strength -1.0
#define EventHorizon 5

BH::BlackHole()
{
	position = sf::Vector2f(static_cast<float>(w / 2), static_cast<float>(h / 2));
	LoadShader();
	framesExisted = 0;
}

BH::BlackHole(float x, float y)
{
	position = sf::Vector2f(x, y);
	LoadShader();
	framesExisted = 0;
}

BH::BlackHole(sf::Vector2f pos)
{
	position = pos;
	LoadShader();
	framesExisted = 0;
}

BH::~BlackHole()
{
	//if (stormblink)
	//	delete stormblink;
}

void BH::Draw()
{
	stormblink->update(framesExisted++, w / 2, h / 2);
	window.draw(*stormblink);
	
	float size = 25;
	sf::CircleShape ball;
	ball.setRadius(size);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(size / 2, size / 2);
	ball.setPosition(position);
	window.draw(ball);
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
	stormblink->load();
}
