#pragma once
#include "Drill.t.hpp"


template <typename t>
Drill<t>::Drill() : Drill(-1) {}

template <typename t>
Drill<t>::Drill(size_t maxPayload)
{
	outputHandle = new InOutConvoyHandle<t>(InOutConvoy::Mode::Out, ResourceType::Unknown, Direction::South);
	outputHandle->payload = new InOutPayload<t>(maxPayload);
	outputHandle->managePayload = true;
	this->addOutput(outputHandle->boxed());
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


template <typename t>
void Drill<t>::preupdate(double dt)
{
	currentDrill += (float)dt;
	while (currentDrill >= drillDelay) {
		currentDrill -= drillDelay;
		performDrill();
	}
}

template <typename t>
void Drill<t>::performDrill()
{
	if (!outputHandle->payload->canPush()) return;
	Payload* payload = PayloadPool::get(1);
	outputHandle->payload->push(payload);
}