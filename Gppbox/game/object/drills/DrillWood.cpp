#include "DrillWood.hpp"

DrillWood::DrillWood() : Drill(C::DRILL_PAYLOAD)
{
	this->nodeType = NodeType::Wood;
	outputHandle->type = ResourceType::Wood;
	outputHandle->anchor = sf::Vector2i(0, 0);
}

DrillWood::~DrillWood()
{
	
}