#include <cstdlib>
#include <ctime>
#include "Shooter.h"
#include "GlobalVariables.h"

#define NumberOfStars 100
#define StarSize 1

Shooter::Shooter()
{
	InitStars();
}

Shooter::~Shooter()
{

}

void Shooter::Update()
{

}

void Shooter::Draw()
{
	window.clear(sf::Color::Black);
	DrawStars();
}

void Shooter::ProcessKeyboardEvent()
{

}

void Shooter::ProcessControllerEvent()
{

}

//This is the starfield that lies behind the game
void Shooter::DrawStars()
{
	for (int i = 0; i < NumberOfStars; i++)
	{
		sf::CircleShape star(StarSize);
		star.setFillColor(sf::Color::White);
		sf::Vector2f pos = starLocations[i];
		star.setPosition(pos);
		window.draw(star);
	}
}

void Shooter::InitStars()
{
	srand(time(nullptr));
	for (int i = 0; i < NumberOfStars; i++)
	{
		sf::Vector2f pos(rand() % w, rand() % h);
		starLocations.push_back(pos);
	}
	starLocations.shrink_to_fit();
}