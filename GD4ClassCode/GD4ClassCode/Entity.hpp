#pragma once

class Entity
{
private:
	sf::Vector2f mVelocity;

public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

private:
	virtual void updateCurrent(sf::Time dt);
};