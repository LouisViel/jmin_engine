#include "CrafterPlanksConstructor.hpp"
#include "game/object/crafters/CrafterPlanks.hpp"
#include "app/C.hpp"

CrafterPlanksConstructor::CrafterPlanksConstructor() :
	CrafterConstructor(
		sf::Vector2i(-1, -1),
		COLLIDER_SIZE_CRAFTER_INT
	)
{ }

Object* CrafterPlanksConstructor::tryBuild()
{
	CrafterPlanks* crafter = new CrafterPlanks();
	return static_cast<Object*>(crafter);
}