#include "DrillWood.hpp"
#include "game/core/utils/RessourceSprite.hpp"

DrillWood::DrillWood() : Drill(C::DRILL_PAYLOAD)
{
	this->nodeType = NodeType::Wood;
	outputHandle->type = ResourceType::Wood;
	outputHandle->anchor = sf::Vector2i(1, 2);
}

DrillWood::~DrillWood()
{
	return;
}

Payload* DrillWood::getPayload()
{
	sf::Drawable* render = RessourceSprite::get(ResourceType::Wood);
	return PayloadPool::get(1, render);
}