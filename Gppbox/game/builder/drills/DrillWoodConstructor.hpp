#pragma once
#include "game/builder/DrillConstructor.hpp"

class DrillWoodConstructor : public DrillConstructor
{
public:
	DrillWoodConstructor();
	DrillWoodConstructor(float speed);
	Object* tryBuild() override;
};
