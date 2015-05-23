#include <exception>
#include "Ship.h"

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
}

Ship::~Ship()
{

}

void Ship::Draw()
{

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

}

void Ship::HandleArrows()
{

}
