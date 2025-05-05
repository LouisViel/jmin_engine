#include "Container.t.hpp"
#include "game/core/object/Collider.hpp"

template <typename t>
Container<t>::Container(ResourceType type, sf::Vector2f colliderSize) : ContainerBase(type)
{
	inputHandle = new InOutConvoyHandle<t>(InOutConvoy::Mode::In, type, Direction::South);
	inputHandle->payload = new InOutPayload<t>();
	inputHandle->managePayload = true;
	this->addInput(inputHandle->boxed());
	this->collider = new Collider(colliderSize);
}

template <typename t>
void Container<t>::update(double dt)
{
	// Read/Update input buffer & input counts
	while (inputHandle->payload->valid()) {
		PayloadBase* payload = static_cast<PayloadBase*>(inputHandle->payload->pop());
		ressourceCount = Utils::safeAdd(ressourceCount, payload->quantity);
		PayloadPool::free(payload);
	}
}