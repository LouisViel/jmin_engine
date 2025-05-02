#pragma once
#include "game/core/builder/BuildConstructor.hpp"

class ConvoyerConstructor : public BuildConstructor
{
public:
	ConvoyerConstructor();
	~ConvoyerConstructor();
	Object* build() override;
};
