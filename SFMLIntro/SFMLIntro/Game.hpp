#pragma once
#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable
{
private:
	static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;

	std::size_t mStatisticsNumFrames;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void draw();

	void updateStatistics(sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key, bool isPressed);
};