#pragma once
#include "game/builder/ConvoyerConstructor.hpp"

class ConvoyerFastConstructor : public ConvoyerConstructor
{
public:
	virtual ~ConvoyerFastConstructor() {}
	ConvoyerFastConstructor() : ConvoyerConstructor()
	{
		this->speed = 8.5f;
	}
};