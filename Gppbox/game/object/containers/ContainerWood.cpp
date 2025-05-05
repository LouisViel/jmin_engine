#include "ContainerWood.hpp"

ContainerWood::ContainerWood() : Container(ResourceType::Wood, COLLIDER_SIZE_CONTAINER)
{
	// Change anchor
	this->inputHandle->anchor = sf::Vector2i(1, 2);

	// Add Renderer
	Renderer* renderer = new Renderer(this, "assets/bdg/container_wood.png");
	renderer->setScale(COLLIDER_SIZE_CONTAINER);
	this->addComponent(renderer);
}

ContainerWood::~ContainerWood()
{
	return;
}