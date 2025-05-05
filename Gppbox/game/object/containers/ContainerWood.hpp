#pragma once
#include "Container.hpp"

typedef PayloadBase ContainerWoodPayload;

class ContainerWood : public Container<ContainerWoodPayload>
{
public:
	ContainerWood();
	virtual ~ContainerWood();
};

