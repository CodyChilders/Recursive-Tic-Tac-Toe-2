#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Ship.h"
#include "BlackHole.h"

class Shooter : public State
{
public:
	Shooter();
	~Shooter();
	void Update() override;
	void Draw() override;
	void ProcessKeyboardEvent() override;
	void ProcessControllerEvent() override;

private:
	std::vector<sf::Vector2f> starLocations;
	Ship* players[2];
	BlackHole blackhole;

	void DrawStars();
	void InitStars();
	void DrawShips();
};