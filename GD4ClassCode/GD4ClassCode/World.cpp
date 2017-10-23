#include "World.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
World::World(sf::RenderWindow& window) 
	:mWindow(window), mWorldView(window.getDefaultView()), 
	mTextures(), mSceneLayers(), mWorldBounds(0.f,0.f,mWorldView.getSize().x, 2000.f),
	mSceneGraph(), mSpawnPosition(mWorldView.getSize().x/2.f, mWorldBounds.height - mWorldView.getSize().y/2),
	mScrollSpeed(-50), mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();
	//prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt) {
	//Scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	//move the player sideways, the scoup planes will follow
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//If the player touches the border switch direction
	if (position.x <= mWorldBounds.left + 50.f || position.x >= mWorldBounds.left + mWorldBounds.width - 50.f) {
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	//apply the movements
	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; i++)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	//prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	//add background sprite to scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	//add players aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	//scroll the player
	mPlayerAircraft->setVelocity(40, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));


	//add two follower aircraft
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
}

/*
void World::adaptPlayerPosition()
{
	//Keep player on the screen
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
	//if movement diagonal reduce velocity (for same velocity in each direction)
	if (velocity.x != 0 && velocity.y != 0)
	{
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
	}

	//add scrolling velocity
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}*/