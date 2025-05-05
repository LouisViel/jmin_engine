#pragma once
#include "Container.hpp"

typedef PayloadBase ContainerPlanksPayload;

class ContainerPlanks : public Container<ContainerPlanksPayload>
{
public:
	ContainerPlanks();
	virtual ~ContainerPlanks();
};

