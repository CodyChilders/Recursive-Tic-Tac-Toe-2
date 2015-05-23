#pragma once
#include <SFML/Audio.hpp>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	void PlayPlacePiece();
	void PlayWinBoard();
	void PlayTie();
	void PlayButton();
	void PlayMainMenu();

private:
	sf::SoundBuffer placeTTTPiece;
	sf::SoundBuffer winTTTBoard;
	sf::SoundBuffer TTTtie;
	sf::SoundBuffer startGameButton;
	sf::SoundBuffer mainMenuMusic;

	void LoadResources();
	void PlayBuffer(sf::SoundBuffer buffer);
};