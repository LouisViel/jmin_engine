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