#include "ProjectileManager.h"

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

void PM::Update(BlackHole* bh)
{
	for (std::list<Projectile*>::iterator it = activeProjectiles.begin(); it != activeProjectiles.end(); ++it)
	{
		if ( !( (*it)->IsActive() ) )
		{
			std::list<Projectile*>::iterator previous = it++;
			activeProjectiles.erase(previous);
			//delete &previous;
			//decide if it should continue or break this loop
			//continue if there is more stuff in the list
			//break if it is the end of the list
			if (it == activeProjectiles.end())
				break;
			else
				continue;
		}
		(*it)->Update(bh);
		(*it)->PullTowardsPoint(bh);
	}
	//printf("Projectiles contains %d elements\n", activeProjectiles.size());
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
	activeProjectiles.push_back(new Projectile(pos, dir, plr));
}
