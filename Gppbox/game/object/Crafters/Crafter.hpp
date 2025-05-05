#pragma once
#include "Crafter.t.hpp"
#include "game/core/object/Collider.hpp"


template <typename t>
Crafter<t>::Crafter(sf::Vector2f colliderSize) : Crafter(colliderSize , -1) { }

template <typename t>
Crafter<t>::Crafter(sf::Vector2f colliderSize, size_t maxPayload)
{
	outputHandle = new InOutConvoyHandle<t>(InOutConvoy::Mode::Out, ResourceType::Unknown, Direction::North);
	outputHandle->setPayload(new InOutPayload<t>(maxPayload), true);
	this->addOutput(outputHandle->boxed());
	this->collider = new Collider(colliderSize);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


template <typename t>
void Crafter<t>::update(double dt)
{
	currentCraft += (float)dt * speed;
	while (currentCraft >= craftDelay) {
		currentCraft -= craftDelay;
		performCraft();
	}
}

template <typename t>
void Crafter<t>::performCraft()
{
	// Ensure correct & valid payload handle
	if (!outputHandle->ensurePayload()) return;

	InOutPayload<t>* payloadHandle = outputHandle->getPayload();
	if (!payloadHandle->canPush()) return;
	Payload* payload = getPayload();
	payloadHandle->push(payload);
	this->craftPerformed();
}

template <typename t>
t* Crafter<t>::getPayload()
{
	return PayloadPool::get(1);
}