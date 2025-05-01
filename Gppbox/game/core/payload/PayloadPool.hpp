#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
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
	static void free(PayloadBase* payload)
	{
		if (singleton == nullptr) delete payload;
		else singleton->freeInternal(payload);
	}

	static PayloadBase* get(int quantity) { return PayloadPool::get(quantity, nullptr); }
	static PayloadBase* get(int quantity, sf::Drawable* render)
	{
		// Get / Create Payload
		PayloadBase* payload;
		if (singleton == nullptr) payload = new PayloadBase();
		else payload = singleton->getInternal();

		// Set Settings
		payload->quantity = quantity;
		payload->render = render;

		// Return results
		return payload;
	}



private:
	PayloadBase* getInternal()
	{
		// Get a pool payload if possible, otherwise allocate it
		if (available->empty()) return new PayloadBase();
		PayloadBase* payload = available->front();
		available->pop();
		return payload;
	}

	void freeInternal(PayloadBase* payload)
	{
		// Free payload whatever
		if (payload->pool) available->emplace(payload);
		else delete payload;
	}
};