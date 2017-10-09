#pragma once
#include "Entity.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "ResourceIdentifiers.hpp"

class Aircraft : public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor
	};

private:
	Type mType;
	sf::Sprite mSprite;

public:
	Aircraft(Type type, const TextureHolder& textures);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};
