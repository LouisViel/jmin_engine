#include "InOutPayload.t.hpp"

template <typename t>
InOutPayload<t>::InOutPayload() : InOutPayload(-1) {}

template <typename t>
InOutPayload<t>::InOutPayload(size_t maxSize) : maxSize(maxSize)
{
	if (maxSize < 0) this->maxSize = std::numeric_limits<size_t>::max();
	payload = new std::queue<t*>();
}

template <typename t>
InOutPayload<t>::~InOutPayload()
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


template <typename t>
bool InOutPayload<t>::valid() const
{
	return !payload->empty();
}

template <typename t>
bool InOutPayload<t>::invalid() const
{
	return payload->empty();
}

template <typename t>
bool InOutPayload<t>::canPush() const
{
	return !locked && payload->size() < maxSize;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


template <typename t>
t* InOutPayload<t>::pop()
{
	t* elem = payload->front();
	payload->pop();
	return elem;
}

template <typename t>
bool InOutPayload<t>::push(t* elem)
{
	if (!canPush()) return false;
	payload->emplace(elem);
	return true;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


template <typename t>
void InOutPayload<t>::empty()
{
	while (!payload->empty()) {
		payload->pop();
	}
}

template <typename t>
std::vector<t*>* InOutPayload<t>::toVector(bool flush)
{
	// Setup result vector
	std::vector<t*>* vector = new std::vector<t*>();

	// Move 1 after another the elements
	while (!payload.empty()) {
		vector->emplace_back(std::move(payload.front()));
		payload.pop();
	}

	// Restore the internal payload if asked to
	if (!flush) for (t* elem : *vector) payload->emplace(elem);
	
	// Return result
	return vector;
}