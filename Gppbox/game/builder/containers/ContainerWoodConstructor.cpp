#include "ContainerWoodConstructor.hpp"
#include "game/object/containers/ContainerWood.hpp"
#include "app/C.hpp"

ContainerWoodConstructor::ContainerWoodConstructor() :
	ContainerConstructor(
		sf::Vector2i(-1, -1),
		COLLIDER_SIZE_CONTAINER_INT
	)
{ }

Object* ContainerWoodConstructor::tryBuild()
{
	ContainerWood* container = new ContainerWood();
	BuildConstructor::copyTransformTo(container);
	container->move((float)anchor.x, (float)anchor.y);
	return static_cast<Object*>(container);
}