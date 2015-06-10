#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "BlackHole.h"

#define speed 8.0f
#define maxProjectileLifetime 150
Projectile::Projectile()
{
	active = true;
	framesSinceBirth = 0;
}

Projectile::Projectile(sf::Vector2f shipPosition, sf::Vector2f direction, int player)
{
	position = shipPosition;
	velocity = direction * speed;
	owner = player;
	active = true;
	framesSinceBirth = 0;
}

Projectile::~Projectile()
{

}

void Projectile::Update(BlackHole* bh)
{
	//actual update information
	position += velocity;
	//see if it fell into the black hole
	float distanceToBH = std::sqrt(std::pow(bh->GetPosition().x - position.x, 2) + std::pow(bh->GetPosition().y - position.y, 2));
	//all the places it could have failed
	
	if (//check if this needs to be deleted because it went of the screen
		position.x < 0 ||
		position.x > w ||
		position.y < 0 ||
		position.y > h ||
		//check if it needs to be deleted because it has been alive too long
		framesSinceBirth++ > maxProjectileLifetime ||
		//check if it got sucked into the black hole
		distanceToBH <= bh->GetEventHorizon()
	   )
	{
		active = false;
		return;
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
	direction *= -0.5f;// bh->GetStrength();
	//make this the new velocity
	velocity -= direction; // misleading variable names, but direction has been turned into velocity
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
