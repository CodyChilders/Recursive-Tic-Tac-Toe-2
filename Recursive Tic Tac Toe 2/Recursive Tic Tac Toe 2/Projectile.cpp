#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "BlackHole.h"

#define speed 8.0f

Projectile::Projectile()
{
	active = true;
}

Projectile::Projectile(sf::Vector2f shipPosition, sf::Vector2f direction, int player)
{
	position = shipPosition;
	velocity = direction * speed;
	owner = player;
	active = true;
}

Projectile::~Projectile()
{

}

void Projectile::Update()
{
	position += velocity;
}

void Projectile::Draw()
{

}

void Projectile::PullTowardsPoint(BlackHole bh)
{
	//find the vector from this to that point
	sf::Vector2f direction = position - bh.GetPosition();
	//normalize
	float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	//see if it died from the black hole
	if (length < bh.GetEventHorizon())
	{
		printf("Mark projectile shot by player %d as dead - not implemented yet\n", owner);
		return;
	}
	//finish resolving the pull
	direction /= length;
	//scale up to the power
	direction *= bh.GetStrength();
	//add to the position
	position += direction;
}

sf::Vector2f Projectile::GetPosition()
{
	return position;
}

sf::Vector2f Projectile::GetVelocity()
{
	return velocity;
}

bool Projectile::IsActive()
{
	return active;
}
