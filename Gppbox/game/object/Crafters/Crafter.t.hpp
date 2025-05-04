#pragma once
#include "game/object/Building.hpp"

template <typename t>
class Crafter : public Building
{
protected:
	InOutConvoyHandle<t>* outputHandle = nullptr;
	float craftDelay = 1.5f;
	float currentCraft = 0.0f;

public:
	Crafter(sf::Vector2f colliderSize);
	Crafter(sf::Vector2f colliderSize, size_t maxPayload);
	virtual ~Crafter() { return; }

	void update(double dt) override;

protected:
	virtual void performCraft();
	virtual void craftPerformed() = 0;
	virtual t* getPayload();
};
