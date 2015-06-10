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
	pm->Update(&blackhole);
	players[0]->PullTowardsPoint(&blackhole);
	players[1]->PullTowardsPoint(&blackhole);
	CheckProjectileCollisions();
	CheckIfShipsAreDead();
}

void Shooter::Draw()
{
	window.clear(sf::Color::Black);
	blackhole.Draw();
	DrawStars();
	//pm->Update( & blackhole);
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

void Shooter::CheckProjectileCollisions()
{
	std::list<Projectile*> activeProjectiles = pm->GetActiveProjectiles();
	for (std::list<Projectile*>::iterator it = activeProjectiles.begin(); it != activeProjectiles.end(); ++it)
	{
		sf::Vector2f position = (*it)->GetPosition();
		for (int i = 0; i <= 1; i++) //Check both the players to see if they have been hit
		{
			if (players[i]->ContainsPoint(position))
			{
				//mark the other player as having won
				//printf("Player %d was hit\n", i + 1);
				if (i == 0) //Mark player 1 as dead
				{
					SetWinningPlayer(2);
				}
				else //Mark player 2 as dead
				{
					SetWinningPlayer(1);
				}
			}
		}
	}
}

void Shooter::SetWinningPlayer(int player)
{
	//printf("Player %d has won\n", player);
	if (contestedBoard)
	{
		contestedBoard->SetWinner(player);
		contestedBoard = nullptr;
	}
	try
	{
		states->PopState();
	}
	catch (std::exception e)
	{
		//This probably means I'm testing and there isn't a state under this.  Just ignore
		return;
	}
}

void Shooter::CheckIfShipsAreDead()
{
	if (players[0]->IsDead())
	{
		SetWinningPlayer(2);
		return;
	}
	if (players[1]->IsDead())
	{
		SetWinningPlayer(1);
		return;
	}
}