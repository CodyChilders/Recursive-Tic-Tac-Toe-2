#pragma once
#include <SFML/Graphics.hpp>
#include "BlackHole.h"

class Projectile
{
public:
	Projectile();
	Projectile(sf::Vector2f shipPosition, sf::Vector2f direction, int player);
	~Projectile();
	void Update();
	void Draw();
	void PullTowardsPoint(BlackHole* bh);
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	bool IsActive();

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	int owner; //which player shot this projectile
	bool active;
};
