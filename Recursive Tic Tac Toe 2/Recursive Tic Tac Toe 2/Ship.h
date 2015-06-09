#pragma once
#include <SFML/Graphics.hpp>
#include "BlackHole.h"
#include "ProjectileManager.h"

class Ship
{
public:
	typedef enum Players{ Player1 = 1, Player2 = 2 };
	typedef int Player;
	Ship();
	Ship(Player p);
	~Ship();
	void Update();
	void Draw();
	void ProcessKeyboardEvent(ProjectileManager* pm);
	void ProcessControllerEvent(ProjectileManager* pm);
	void PullTowardsPoint(BlackHole bh);
	sf::Vector2f GetPosition() { return position; }
	sf::Vector2f GetDirection() { return direction; }
	Player GetPlayer() { return config; }

private:
	Player config;
	sf::Vector2f position;
	sf::Vector2f direction;
	float velocity;

	sf::Sprite sprite;
	sf::Texture texture;

	void ShootProjectile(ProjectileManager* pm);
	void HandleWASD(ProjectileManager* pm);
	void HandleArrows(ProjectileManager* pm);
	void InitPlayer1Settings();
	void InitPlayer2Settings();
	void UpdatePosition();
	void RotateShip(float angle);
	void DrawShip();
};
