#include "BuildConstructor.hpp"
#include "engine/utils/ScaleHelper.hpp"

void BuildConstructor::destroyAt(Game* game)
{
	// TODO : Implement (via game & world)
	// Default implementation => destroy under cursor if possible
}

void BuildConstructor::setTargetPosition(sf::Vector2i pos)
{
	this->setPosition((float)pos.x, (float)pos.y);
}

void BuildConstructor::applyTransform(sf::RenderStates& states) const
{
	states.transform *= getTransform();
	//states.transform *= ScaleHelper::invert();
}

void BuildConstructor::copyTransformTo(sf::Transformable* other) const
{
	other->setOrigin(getOrigin());
	other->setPosition(getPosition());
	other->setRotation(getRotation());
	other->setScale(getScale());
}