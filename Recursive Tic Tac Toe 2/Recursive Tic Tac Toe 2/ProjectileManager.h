#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "BlackHole.h"

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();
	void Update(BlackHole* bh);
	void Draw();
	void FireProjectile(sf::Vector2f pos, sf::Vector2f dir, int plr);
	std::list<Projectile*> GetActiveProjectiles() { return activeProjectiles; }

private:
	std::list<Projectile*> activeProjectiles;
};
