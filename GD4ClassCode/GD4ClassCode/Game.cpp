#include "Game.hpp"
#include <SFML/Window/Event.hpp>
#include "StringHelpers.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Scene Graph", sf::Style::Close),
mWorld(mWindow), mFont(), mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames()
{
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		draw();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTame)
{
	mWorld.update(elapsedTame);
}

void Game::draw()
{
	mWindow.clear();
	mWorld.draw();
	//make sure text is always in the same place
	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTame)
{
	mStatisticsUpdateTime += elapsedTame;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime > sf::seconds(1.0f)) {
		mStatisticsText.setString("Fames/Second = " + toString(mStatisticsNumFrames) + "\n" + "Time/Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames));
		mStatisticsUpdateTime -= sf::seconds(1.f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
}