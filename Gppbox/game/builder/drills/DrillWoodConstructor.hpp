#pragma once
#include "game/builder/DrillConstructor.hpp"

class DrillWoodConstructor : public DrillConstructor
{
public:
	DrillWoodConstructor();
	Object* tryBuild() override;
};
