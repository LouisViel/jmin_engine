#include "ContainerPlanks.hpp"

ContainerPlanks::ContainerPlanks() : Container(ResourceType::Planks, COLLIDER_SIZE_CONTAINER)
{
	// Change anchor
	this->inputHandle->anchor = sf::Vector2i(1, 2);

	// Add Renderer
	Renderer* renderer = new Renderer(this, "assets/bdg/container_planks.png");
	renderer->setScale(COLLIDER_SIZE_CONTAINER);
	this->addComponent(renderer);
}

ContainerPlanks::~ContainerPlanks()
{
	return;
}