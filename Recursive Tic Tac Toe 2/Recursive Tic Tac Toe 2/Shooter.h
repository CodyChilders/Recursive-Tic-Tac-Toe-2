#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "State.h"

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
	void DrawStars();
	void InitStars();
};