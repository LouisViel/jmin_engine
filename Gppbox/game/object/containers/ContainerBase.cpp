#include "ContainerBase.hpp"
#include "game/core/ContainerManager.hpp"

ContainerBase::ContainerBase(ResourceType type) : type(type)
{
	ContainerManager::add(type, this);
}

ContainerBase::~ContainerBase()
{
	ContainerManager::remove(type, this);
}