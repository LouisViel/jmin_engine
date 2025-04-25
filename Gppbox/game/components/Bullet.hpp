#pragma once
#include "Component.hpp"

class Bullet : public Component
{
public:
	float damages = 10.0f;
	Bullet(Object* object);
	Bullet(Object* object, float damages);
	void fixed(double fdt) override;
};