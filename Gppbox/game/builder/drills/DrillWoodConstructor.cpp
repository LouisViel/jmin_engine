#include "DrillWoodConstructor.hpp"
#include "game/object/drills/DrillWood.hpp"
#include "app/C.hpp"

DrillWoodConstructor::DrillWoodConstructor() :
	DrillConstructor(
		sf::Vector2i(-1, -1),
		COLLIDER_SIZE_DRILL_INT,
		NodeType::Wood
	)
{ }

Object* DrillWoodConstructor::tryBuild()
{
	DrillWood* drill = new DrillWood();
	BuildConstructor::copyTransformTo(drill);
	drill->move((float)anchor.x, (float)anchor.y);
	return static_cast<Object*>(drill);
}