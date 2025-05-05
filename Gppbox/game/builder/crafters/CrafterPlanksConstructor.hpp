#pragma once
#include "game/builder/CrafterConstructor.hpp"

class CrafterPlanksConstructor : public CrafterConstructor
{
public:
	CrafterPlanksConstructor();
	CrafterPlanksConstructor(float speed);
	Object* tryBuild() override;
};

