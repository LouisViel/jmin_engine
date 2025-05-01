#pragma once
#include "InOutPayload.t.hpp"

template <typename t>
bool InOutPayload<t>::push(t* elem)
{
	if (!canPush()) return false;
	payload->emplace((PayloadBase*)elem);
	return true;
}

template <typename t>
t* InOutPayload<t>::pop()
{
	t* elem = (t*)payload->front();
	payload->pop();
	return elem;
}

template <typename t>
std::vector<t*>* InOutPayload<t>::toVector(bool flush)
{
	// Setup result vector
	std::vector<t*>* vector = new std::vector<t*>();

	// Move 1 after another the elements
	while (!payload.empty()) {
		vector->emplace_back((t*)payload.front());
		payload.pop();
	}

	// Restore the internal payload if asked to
	if (!flush) for (t* elem : *vector)
		payload->emplace((PayloadBase*)elem);
	
	// Return result
	return vector;
}