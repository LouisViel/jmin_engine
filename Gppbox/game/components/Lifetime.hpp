#pragma once
#include "Component.hpp"

class Lifetime : public Component
{
private:
	float lifetime = 0.0f;

public:
	Lifetime(Object* object, float lifetime);
	void preupdate(double dt) override;
};