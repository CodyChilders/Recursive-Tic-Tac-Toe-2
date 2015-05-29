#pragma once
#include <SFML/Graphics.hpp>

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
	void ProcessKeyboardEvent();
	void ProcessControllerEvent();

private:
	Player config;
	sf::Vector2f position;
	sf::Vector2f velocity;

	void ShootProjectile();
	void HandleWASD();
	void HandleArrows();
	void InitPlayer1Settings();
	void InitPlayer2Settings();
	void UpdatePosition();
	void RotateShip(float angle);
	void DrawShip();
};
