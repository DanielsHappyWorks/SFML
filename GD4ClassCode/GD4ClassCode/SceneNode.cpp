#include "SceneNode.hpp"
#include <algorithm>
#include <cassert>

SceneNode::SceneNode()
	:mChildren(), mParent(nullptr)
{

}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detatchChild(const SceneNode& node)
{
	//uses a lamda function
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());
	Ptr res = std::move(*found);
	res->mParent = nullptr;
	mChildren.erase(found);
	return res;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		transform = node->getTransform() * transform;
	}
	return transform;
}

void SceneNode::updateCurrent(sf::Time dt)
{
	//Do nothing be default
}
void SceneNode::updateChildren(sf::Time dt)
{
	for (const Ptr& child : mChildren) {
		child->update(dt);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);
}
void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//do nothing by default
}
void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : mChildren) {
		child->draw(target, states);
	}
}