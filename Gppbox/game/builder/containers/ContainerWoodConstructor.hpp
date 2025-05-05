#pragma once
#include "game/builder/ContainerConstructor.hpp"

class ContainerWoodConstructor : public ContainerConstructor
{
public:
	ContainerWoodConstructor();
	Object* tryBuild() override;
};

