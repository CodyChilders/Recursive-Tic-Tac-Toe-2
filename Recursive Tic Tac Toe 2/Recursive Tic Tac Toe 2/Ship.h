#pragma once

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

private:
	Player config;

	void ShootProjectile();
	void HandleWASD();
	void HandleArrows();
};
