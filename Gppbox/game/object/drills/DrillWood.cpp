#include "DrillWood.hpp"

DrillWood::DrillWood() : Drill(C::DRILL_PAYLOAD)
{
	this->nodeType = NodeType::Wood;
	outputHandle->anchor = sf::Vector2i(0, 0);
	outputHandle->type = ResourceType::Wood;
}

DrillWood::~DrillWood()
{

}