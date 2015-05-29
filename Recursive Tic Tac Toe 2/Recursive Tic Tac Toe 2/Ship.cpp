#include <exception>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "GlobalVariables.h"

#define SPEED 2
#define DampenFactor 0.9

Ship::Ship()
{

}

Ship::Ship(Player p)
{
	if ( !(p == Player1 || p == Player2) )
	{
		throw new std::exception("ERROR: can not create a ship with a player that isn't Player1 or Player2");
	}
	config = p;
	switch (p)
	{
	case Player1:
		InitPlayer1Settings();
		break;
	case Player2:
		InitPlayer2Settings();
	}
}

Ship::~Ship()
{

}

void Ship::Draw()
{
	//Update the ship's position
	UpdatePosition();
	//Draw the ship
	DrawShip();
}

void Ship::ProcessKeyboardEvent()
{
	if (config == Player1)
	{
		HandleWASD();
	}
	else if (config == Player2)
	{
		HandleArrows();
	}
	else
	{
		throw new std::exception("ERROR: player config in the ship set to an invalid player");
	}
}

void Ship::ShootProjectile()
{

}

void Ship::HandleWASD()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += SPEED;
	}
}

void Ship::HandleArrows()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y -= SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y += SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += SPEED;
	}
}

void Ship::InitPlayer1Settings()
{
	position = sf::Vector2f(w / 4, h / 2);
}

void Ship::InitPlayer2Settings()
{
	position = sf::Vector2f(3 * w / 4, h / 2);
}

void Ship::UpdatePosition()
{
	position += velocity;
	velocity.x *= DampenFactor;
	velocity.y *= DampenFactor;
}

void Ship::DrawShip()
{
	sf::CircleShape ball;
	ball.setRadius(10);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(5, 5);
	ball.setPosition(position);
	window.draw(ball);
}
