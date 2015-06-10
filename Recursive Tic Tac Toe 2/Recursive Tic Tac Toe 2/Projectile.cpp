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
	//check if this needs to be deleted because it went of the screen
	if (position.x < 0 ||
		position.x > w ||
		position.y < 0 ||
		position.y > h)
	{
		active = false;
	}
}

void Projectile::Draw()
{
	sf::CircleShape ball;
	ball.setRadius(4);
	ball.setOutlineThickness(3);
	if (owner == 1)
	{
		ball.setOutlineColor(sf::Color::Red);
		ball.setFillColor(sf::Color::Red);
	}
	else
	{
		ball.setOutlineColor(sf::Color::Blue);
		ball.setFillColor(sf::Color::Blue);
	}
	ball.setOrigin(5, 5);
	ball.setPosition(position);
	window.draw(ball);
}

void Projectile::PullTowardsPoint(BlackHole* bh)
{
	//find the vector from this to that point
	sf::Vector2f direction = position - bh->GetPosition();
	//get the length of the vector for normalizing
	float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	//see if it died from the black hole
	if (length < bh->GetEventHorizon())
	{
		active = false;
		return;
	}
	//finish normalizing
	direction /= length;
	//modify the velocity vector to be the normal of the ray from this to the black hole
	float angle = 90.0f;
	direction.x = direction.x * cos(angle) - direction.y * sin(angle);
	direction.y = direction.x * sin(angle) + direction.y * cos(angle);
	//scale up to the power
	direction *= bh->GetStrength();
	//make this the new velocity
	velocity = direction; // misleading variable names, but direction has been turned into velocity
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
