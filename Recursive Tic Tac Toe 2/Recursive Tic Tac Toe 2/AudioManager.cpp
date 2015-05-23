#include <SFML/Audio.hpp>
#include <iostream>
#include "AudioManager.h"

#define AM AudioManager

#define placePieceSound "../Sounds/"
#define winTTTSound "../Sounds/"
#define TTTtieSound "../Sounds/"
#define startGame "../Sounds/zwoo.wav"
#define mainMenuTheme "../Sounds/"

AM::AudioManager()
{
	LoadResources();
}

AM::~AudioManager()
{

}

void AM::PlayPlacePiece()
{
	PlayBuffer(placeTTTPiece);
}

void AM::PlayWinBoard()
{
	PlayBuffer(winTTTBoard);
}

void AM::PlayTie()
{
	PlayBuffer(TTTtie);
}

void AM::PlayButton()
{
	PlayBuffer(startGameButton);
}

void AM::PlayMainMenu()
{
	PlayBuffer(mainMenuMusic);
}

void AM::LoadResources()
{
	if (!placeTTTPiece.loadFromFile(placePieceSound))
		std::cout << "Failed to load sound " << placePieceSound << std::endl;
	if (!winTTTBoard.loadFromFile(winTTTSound))
		std::cout << "Failed to load sound " << winTTTSound << std::endl;
	if (!TTTtie.loadFromFile(TTTtieSound))
		std::cout << "Failed to load sound " << TTTtieSound << std::endl;
	if (!startGameButton.loadFromFile(startGame))
		std::cout << "Failed to load sound " << startGame << std::endl;
	if (!mainMenuMusic.loadFromFile(mainMenuTheme))
		std::cout << "Failed to load sound " << mainMenuTheme << std::endl;
}

void AM::PlayBuffer(sf::SoundBuffer buffer)
{
	sf::Sound sound(buffer);
	sound.play();
}