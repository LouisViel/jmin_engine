#pragma once
#include "Component.hpp"

class PlayerController : public Component
{
public:
	PlayerController(Object* object);

	void preupdate(double dt) override;
	void update(double dt) override;

private:
	void processInputs(double dt);
};