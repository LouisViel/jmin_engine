#pragma once
#include "game/object/Building.hpp"
#include "app/C.hpp"

template <typename t>
class Drill : public Building
{
protected:
	InOutConvoyHandle<t>* outputHandle = nullptr;
	float drillDelay = 1.5f;
	float currentDrill = 0.0f;

public:
	Drill();
	Drill(size_t maxPayload);
	virtual ~Drill() { return; }

	void preupdate(double dt) override;

protected:
	virtual void performDrill();
	virtual t* getPayload();
};
