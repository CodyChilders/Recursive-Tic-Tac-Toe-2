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
		printf("DEBUG: ProjectileManager.cpp is not checking if this projectile should be deleted\n");
		(*it)->Update();
	}
}

void PM::Draw()
{
	for (std::list<Projectile*>::iterator it = activeProjectiles.begin(); it != activeProjectiles.end(); ++it)
	{
		(*it)->Draw();
	}
}

void PM::FireProjectile(Ship* s)
{
	Projectile* newProjectile = nullptr;
	sf::Vector2f pos = s->GetPosition();
	sf::Vector2f dir = s->GetDirection();
	int plr = s->GetPlayer();
	newProjectile = new Projectile(pos, dir, plr);
	activeProjectiles.push_back(newProjectile);
}
