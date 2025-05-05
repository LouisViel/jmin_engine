#pragma once
#include "game/builder/ConvoyerConstructor.hpp"

class ConvoyerMeanConstructor : public ConvoyerConstructor
{
public:
	virtual ~ConvoyerMeanConstructor() {}
	ConvoyerMeanConstructor() : ConvoyerConstructor()
	{
		this->speed = 4.0f;
	}
};