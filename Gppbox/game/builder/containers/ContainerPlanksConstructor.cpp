#include "ContainerPlanksConstructor.hpp"
#include "game/object/containers/ContainerPlanks.hpp"
#include "app/C.hpp"

ContainerPlanksConstructor::ContainerPlanksConstructor() :
	ContainerConstructor(
		sf::Vector2i(-1, -1),
		COLLIDER_SIZE_CONTAINER_INT
	)
{ }

Object* ContainerPlanksConstructor::tryBuild()
{
	ContainerPlanks* container = new ContainerPlanks();
	BuildConstructor::copyTransformTo(container);
	container->move((float)anchor.x, (float)anchor.y);
	return static_cast<Object*>(container);
}