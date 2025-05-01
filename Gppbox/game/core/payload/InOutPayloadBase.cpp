#include "InOutPayloadBase.hpp"

InOutPayloadBase::InOutPayloadBase() : InOutPayloadBase(-1) {}

InOutPayloadBase::InOutPayloadBase(size_t maxSize) : maxSize(maxSize)
{
	if (maxSize < 0) this->maxSize = std::numeric_limits<size_t>::max();
	payload = new std::queue<PayloadBase*>();
}

InOutPayloadBase::~InOutPayloadBase()
{
	while (!payload->empty()) {
		delete payload->front();
		payload->pop();
	}
	delete payload;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool InOutPayloadBase::valid() const
{
	return !payload->empty();
}

bool InOutPayloadBase::invalid() const
{
	return payload->empty();
}

bool InOutPayloadBase::canPush() const
{
	return !locked && payload->size() < maxSize;
}

void InOutPayloadBase::empty()
{
	while (!payload->empty()) {
		payload->pop();
	}
}