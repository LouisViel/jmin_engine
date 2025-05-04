#pragma once
#include "game/builder/CrafterConstructor.hpp"

class CrafterPlanksConstructor : public CrafterConstructor
{
public:
	CrafterPlanksConstructor();
	Object* tryBuild() override;
};

