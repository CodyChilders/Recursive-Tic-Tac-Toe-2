#include <exception>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "BlackHole.h"
#include "GlobalVariables.h"

#define SPEED 5
#define RotationSpeed 0.1
#define DampenFactor 0.9
#define BrakePower 0.7
#define PI 3.141593f
#define ShipImage "../Images/debug_ship.png"

Ship::Ship()
{

}

Ship::Ship(Player p)
{
	//Did I fuck up somewhere else?
	if ( !(p == Player1 || p == Player2) )
	{
		throw new std::exception("ERROR: can not create a ship with a player that isn't Player1 or Player2");
	}
	//Set it so this ship knows what player it is
	config = p;
	//Set up some initial settings based on the player
	switch (p)
	{
	case Player1:
		InitPlayer1Settings();
		break;
	case Player2:
		InitPlayer2Settings();
		break;
	}
	//Set it to not move at all
	velocity = 0;
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

void Ship::ProcessControllerEvent()
{

}

void Ship::PullTowardsPoint(BlackHole bh)
{
	//find the vector from this to that point
	sf::Vector2f direction = position - bh.GetPosition();
	//normalize
	float length = sqrt( pow(direction.x, 2) + pow(direction.y, 2));
	//see if it died from the black hole
	if (length < bh.GetEventHorizon())
	{
		printf("Mark ship %d as dead - not implemented yet\n", config);
		return;
	}
	//finish resolving the pull
	direction /= length;
	//scale up to the power
	direction *= bh.GetStrength();
	//add to the position
	position += direction;
}

void Ship::ShootProjectile()
{

}

void Ship::HandleWASD()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity = SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		RotateShip(-RotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity *= BrakePower;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		RotateShip(RotationSpeed);
	}
}

void Ship::HandleArrows()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity = SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		RotateShip(-RotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity *= BrakePower;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		RotateShip(RotationSpeed);
	}
}

void Ship::InitPlayer1Settings()
{
	//set up the technical details
	position = sf::Vector2f(w / 4, h / 2);
	direction = sf::Vector2f(0, -1);
	//load the sprite
	if (!texture.loadFromFile(ShipImage))
	{
		printf("ERROR: can not load image %s\n", ShipImage);
	}
	texture.setSmooth(true);
	sprite = sf::Sprite(texture);
	sprite.setOrigin(sf::Vector2f(texture.getSize()) / 2.f);
}

void Ship::InitPlayer2Settings()
{
	//set up the technical details
	position = sf::Vector2f(3 * w / 4, h / 2);
	direction = sf::Vector2f(0, 1);
	//load the sprite
	if (!texture.loadFromFile(ShipImage))
	{
		printf("ERROR: can not load image %s\n", ShipImage);
	}
	texture.setSmooth(true);
	sprite = sf::Sprite(texture);
	sprite.setOrigin(sf::Vector2f(texture.getSize()) / 2.f);
}

void Ship::UpdatePosition()
{
	position += direction * velocity;
	velocity *= DampenFactor;
	//check if it is out of bounds
	if (position.x > w)
		position.x -= w;
	if (position.x < 0)
		position.x += w;
	if (position.y > h)
		position.y -= h;
	if (position.y < 0)
		position.y += h;
}

void Ship::RotateShip(float angle)
{
	direction.x = direction.x * cos(angle) - direction.y * sin(angle);
	direction.y = direction.x * sin(angle) + direction.y * cos(angle);
}

void Ship::DrawShip()
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
	//set the position and rotation
	sprite.setPosition(position);
	sf::Vector2f reference(1, 0);
	float dot = direction.x * reference.x + direction.y * reference.y;
	float det = direction.x * reference.y - direction.y * reference.x;
	float angle = atan2(det, dot);
	//convert to degrees
	angle *= 180 / PI;
	angle *= -1;
	//rotate an extra 90 so it lines up with the vector
	angle += 90;
	//set the sprite and draw
	sprite.setRotation(angle);
	window.draw(sprite);
	//Draw the 4 ghost ships so that the transition is always seamless
	sf::Vector2f p1(position.x + w, position.y);
	sf::Vector2f p2(position.x - w, position.y);
	sf::Vector2f p3(position.x, position.y + h);
	sf::Vector2f p4(position.x, position.y - h);
	sprite.setPosition(p1);
	window.draw(sprite);
	sprite.setPosition(p2);
	window.draw(sprite);
	sprite.setPosition(p3);
	window.draw(sprite);
	sprite.setPosition(p4);
	window.draw(sprite);
}
