#include <cstdlib>
#include <ctime>
#include "Shooter.h"
#include "GlobalVariables.h"
#include "ProjectileManager.h"

#define NumberOfStars 100
#define StarSize 1

Shooter::Shooter()
{
	InitStars();
	players[0] = new Ship(Ship::Player1);
	players[1] = new Ship(Ship::Player2);
	blackhole = BlackHole(static_cast<float>(w / 2), static_cast<float>(h / 2));
	pm = new ProjectileManager();
}

Shooter::~Shooter()
{
	delete players[0];
	delete players[1];
	delete pm;
}

void Shooter::Update()
{
	pm->Update();
	players[0]->PullTowardsPoint(blackhole);
	players[1]->PullTowardsPoint(blackhole);
}

void Shooter::Draw()
{
	window.clear(sf::Color::Black);
	blackhole.Draw();
	DrawStars();
	pm->Update();
	pm->Draw();
	DrawShips();
}

void Shooter::ProcessKeyboardEvent()
{
	players[0]->ProcessKeyboardEvent(pm);
	players[1]->ProcessKeyboardEvent(pm);
}

void Shooter::ProcessControllerEvent()
{
	players[0]->ProcessControllerEvent(pm);
	players[1]->ProcessControllerEvent(pm);
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
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < NumberOfStars; i++)
	{
		sf::Vector2f pos(static_cast<float>(rand() % w), static_cast<float>(rand() % h));
		starLocations.push_back(pos);
	}
	starLocations.shrink_to_fit();
}

void Shooter::DrawShips()
{
	players[0]->Draw();
	players[1]->Draw();
}
