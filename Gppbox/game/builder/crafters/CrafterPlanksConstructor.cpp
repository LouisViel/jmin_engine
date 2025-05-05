#include "CrafterPlanksConstructor.hpp"
#include "game/object/crafters/CrafterPlanks.hpp"
#include "app/C.hpp"

CrafterPlanksConstructor::CrafterPlanksConstructor() :
	CrafterConstructor(
		sf::Vector2i(-1, -1),
		COLLIDER_SIZE_CRAFTER_INT
	)
{ }

CrafterPlanksConstructor::CrafterPlanksConstructor(float speed) :
	CrafterConstructor(
		sf::Vector2i(-1, -1),
		COLLIDER_SIZE_CRAFTER_INT
	)
{
	this->speed = speed;
}

Object* CrafterPlanksConstructor::tryBuild()
{
	CrafterPlanks* crafter = new CrafterPlanks();
	crafter->speed = this->speed;
	BuildConstructor::copyTransformTo(crafter);
	crafter->move((float)anchor.x, (float)anchor.y);
	return static_cast<Object*>(crafter);
}