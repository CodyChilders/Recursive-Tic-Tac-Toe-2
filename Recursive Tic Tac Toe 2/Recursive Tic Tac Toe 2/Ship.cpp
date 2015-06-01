#include <exception>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "GlobalVariables.h"

#define SPEED 5
#define RotationSpeed 0.1
#define DampenFactor 0.9
#define PI 3.141593
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
		//apply a brake
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
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		
	}
}

void Ship::InitPlayer1Settings()
{
	//set up the technical details
	position = sf::Vector2f(w / 4, h / 2);
	direction = sf::Vector2f(0, -1);
	//load the sprite
	sf::Texture texture;
	if (!texture.loadFromFile(ShipImage))
	{
		printf("ERROR: can not load image %s\n", ShipImage);
	}
	sprite = sf::Sprite(texture);
	sprite.setOrigin(sf::Vector2f(texture.getSize()) / 2.f);
}

void Ship::InitPlayer2Settings()
{
	//set up the technical details
	position = sf::Vector2f(3 * w / 4, h / 2);
	direction = sf::Vector2f(0, 1);
	//load the sprite
	sf::Texture texture;
	if (!texture.loadFromFile(ShipImage))
	{
		printf("ERROR: can not load image %s\n", ShipImage);
	}
	sprite = sf::Sprite(texture);
	sprite.setOrigin(sf::Vector2f(texture.getSize()) / 2.f);
}

void Ship::UpdatePosition()
{
	position += direction * velocity;
	velocity *= DampenFactor;
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
	//set the sprite and draw
	sprite.setRotation(angle);
	window.draw(sprite);
}
