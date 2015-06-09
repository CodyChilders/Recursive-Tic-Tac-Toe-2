#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Ship.h"

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();
	void Update();
	void Draw();
	void FireProjectile(Ship* s);

private:
	std::list<Projectile*> activeProjectiles;
};
