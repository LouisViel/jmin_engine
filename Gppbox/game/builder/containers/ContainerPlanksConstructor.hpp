#pragma once
#include "game/builder/ContainerConstructor.hpp"

class ContainerPlanksConstructor : public ContainerConstructor
{
public:
	ContainerPlanksConstructor();
	Object* tryBuild() override;
};

