#pragma once
#include "Component.hpp"

class PlayerController : public Component
{
public:
	PlayerController(Object* object);

	void preupdate(double dt) override;
	void fixed(double fdt) override;
	void update(double dt) override;
	void imgui() override;

private:
	float coyoteeTime = 0.0f;
	float jumpDelay = 0.0f;

	void processInputs(double dt);
};