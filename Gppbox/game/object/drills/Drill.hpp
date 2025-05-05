#pragma once
#include "Drill.t.hpp"
#include "game/core/object/Collider.hpp"
#include "app/C.hpp"


template <typename t>
Drill<t>::Drill() : Drill(-1) {}

template <typename t>
Drill<t>::Drill(size_t maxPayload)
{
	outputHandle = new InOutConvoyHandle<t>(InOutConvoy::Mode::Out, ResourceType::Unknown, Direction::South);
	outputHandle->setPayload(new InOutPayload<t>(maxPayload), true);
	this->addOutput(outputHandle->boxed());
	this->collider = new Collider(COLLIDER_SIZE_DRILL);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


template <typename t>
void Drill<t>::preupdate(double dt)
{
	Building::preupdate(dt);
	currentDrill += (float)dt * speed;
	while (currentDrill >= drillDelay) {
		currentDrill -= drillDelay;
		performDrill();
	}
}

template <typename t>
void Drill<t>::performDrill()
{
	if (!outputHandle->ensurePayload()) return;
	InOutPayload<t>* payloadHandle = outputHandle->getPayload();
	if (!payloadHandle->canPush()) return;
	Payload* payload = getPayload();
	payloadHandle->push(payload);
}

template <typename t>
t* Drill<t>::getPayload()
{
	return PayloadPool::get(1);
}