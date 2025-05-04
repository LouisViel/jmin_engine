#pragma once
#include "game/builder/ConvoyerConstructor.hpp"

class ConvoyerSlowConstructor : public ConvoyerConstructor
{
public:
	virtual ~ConvoyerSlowConstructor() {}
	ConvoyerSlowConstructor() : ConvoyerConstructor()
	{
		this->speed = 1.0f;
	}
};