#pragma once
#include <map>
#include <queue>
#include "Payload.hpp"
#include "app/C.hpp"

class PayloadPool
{
private:
	static inline PayloadPool* singleton;
	std::queue<PayloadBase*>* available = nullptr;

private:
	PayloadPool()
	{
		singleton = this;
		available = new std::queue<PayloadBase*>();
		for (unsigned int i = 0; i < C::PAYLOAD_POOL_SIZE; ++i)
			available->emplace(new PayloadBase(true));
	}

	~PayloadPool()
	{
		// Delete Available Payloads
		while (!available->empty()) {
			delete available->front();
			available->pop();
		}
		delete available;
	}

public:
	// For Setup only !!
	static void init() { singleton = new PayloadPool(); }
	// For Setup only !!
	static void release() { delete singleton; singleton = nullptr; }

public:
	static PayloadBase* get(int quantity) { return singleton->getInternal(quantity); }
	static void free(PayloadBase* payload) { return singleton->freeInternal(payload); }

private:
	PayloadBase* getInternal(int quantity)
	{
		// Get a pool payload if possible, otherwise allocate it
		if (available->empty()) return new PayloadBase(quantity);
		PayloadBase* payload = available->front();
		available->pop();
		payload->quantity = quantity;
		return payload;
	}

	void freeInternal(PayloadBase* payload)
	{
		// Free payload whatever
		if (payload->pool) available->emplace(payload);
		else delete payload;
	}
};