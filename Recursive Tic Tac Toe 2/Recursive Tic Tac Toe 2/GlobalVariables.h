#pragma once
#include <SFML/Graphics.hpp>

//the window instance
extern sf::RenderWindow window;
extern sf::Color backgroundColor;
extern bool playerOnesTurn;
//the global width and height of the entire window
extern int w;
extern int h;
//mouse position, so I can access it globally easily
extern int mouseX;
extern int mouseY;
