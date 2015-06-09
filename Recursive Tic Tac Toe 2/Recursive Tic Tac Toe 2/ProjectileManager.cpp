#include "ProjectileManager.h"
#include "Ship.h"

#define PM ProjectileManager

PM::ProjectileManager()
{

}

PM::~ProjectileManager()
{
	while (!activeProjectiles.empty())
	{
		Projectile* front = activeProjectiles.front();
		delete front;
		activeProjectiles.pop_front();
	}
}

void PM::Update()
{
	for (std::list<Projectile*>::iterator it = activeProjectiles.begin(); it != activeProjectiles.end(); ++it)
	{
		//printf("DEBUG: ProjectileManager.cpp is not checking if this projectile should be deleted\n");
		if ( !( (*it)->IsActive() ) )
		{
			std::list<Projectile*>	::iterator previous = it++;
			activeProjectiles.erase(previous);
			//decide if it should continue or break this loop
			//continue if there is more stuff in the list
			//break if it is the end of the list
			if (it == activeProjectiles.end())
				break;
			else
				continue;
		}
		(*it)->Update();
	}
	printf("Projectiles contains %d elements\n", activeProjectiles.size());
}

void PM::Draw()
{
	for (std::list<Projectile*>::iterator it = activeProjectiles.begin(); it != activeProjectiles.end(); ++it)
	{
		(*it)->Draw();
	}
}

void PM::FireProjectile(sf::Vector2f pos, sf::Vector2f dir, int plr)
{
	Projectile* newProjectile = new Projectile(pos, dir, plr);
	activeProjectiles.push_back(newProjectile);
}
