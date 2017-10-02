#include "Game.hpp"
#include "StringHelpers.hpp"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() : mWindow(sf::VideoMode(800, 400), "First SFML game", sf::Style::Close), mTexture(), mPlayer(), 
mFont(), mStatisticsUpdateTime(), mStatisticsNumFrames(0),
mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false), mIsMovingLeft(false)
{
	if (mTexture.loadFromFile("Media/Textures/Eagle.png")) {
		//Handle loading error
	}

	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(20);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while(timeSinceLastUpdate > TimePerFrame) {
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
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp) {
		if (mPlayer.getPosition().y>0) {
			movement.y -= PlayerSpeed;
		}
	}
	if (mIsMovingDown) {
		if (mPlayer.getPosition().y < 400-64) {
			movement.y += PlayerSpeed;
		}
	}
	if (mIsMovingLeft) {
		if (mPlayer.getPosition().x > 0) {
			movement.x -= PlayerSpeed;
		}
	}
	if (mIsMovingRight) {
		if (mPlayer.getPosition().x < 800-48) {
			movement.x += PlayerSpeed;
		}
	}

	if ((mIsMovingUp && mIsMovingLeft) || (mIsMovingDown && mIsMovingLeft) ||
		(mIsMovingUp && mIsMovingRight) || (mIsMovingDown && mIsMovingRight)) {
		movement.y = movement.y / sqrt(2.f);
		movement.x = movement.x / sqrt(2.f);
	}

	mPlayer.move(movement * elapsedTame.asSeconds());
}

void Game::draw()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTame)
{
	mStatisticsUpdateTime += elapsedTame;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime > sf::seconds(1.0f)) {
		mStatisticsText.setString("Fames/Second = " + toString(mStatisticsNumFrames) + "\n" + "Time/Update = " + toString(mStatisticsUpdateTime.asMicroseconds()/mStatisticsNumFrames));
		mStatisticsUpdateTime -= sf::seconds(1.f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W) {
		mIsMovingUp = isPressed;
	}
	if (key == sf::Keyboard::S) {
		mIsMovingDown = isPressed;
	}
	if (key == sf::Keyboard::A) {
		mIsMovingLeft = isPressed;
	}
	if (key == sf::Keyboard::D) {
		mIsMovingRight = isPressed;
	}
}