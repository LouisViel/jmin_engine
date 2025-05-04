#include "DrillWood.hpp"
#include "game/core/utils/RessourceSprite.hpp"

DrillWood::DrillWood() : Drill(C::DRILL_PAYLOAD)
{
	this->nodeType = NodeType::Wood;
	outputHandle->type = ResourceType::Wood;
	outputHandle->anchor = sf::Vector2i(1, 2);

	// Add Renderer
	Renderer* renderer = new Renderer(this, "assets/bdg/drill_wood.png");
	renderer->setScale(COLLIDER_SIZE_DRILL);
	this->addComponent(renderer);
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