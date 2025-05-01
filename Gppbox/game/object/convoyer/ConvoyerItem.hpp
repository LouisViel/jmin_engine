#pragma once
#include "game/core/payload/PayloadPool.hpp"
#include "game/core/payload/Payload.hpp"

#include <queue>
#include <SFML/Graphics.hpp>
#include "app/C.hpp"


struct ConvoyerItem
{
private:
	friend class ConvoyerItemPool;
	bool pool = false;
	ConvoyerItem() : pool(true), payload(nullptr) { }

public:
	PayloadBase* payload;
	float progression = 0.0;
	sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f);

	ConvoyerItem(PayloadBase* payload) : payload(payload) { }
	~ConvoyerItem()
	{
		if (payload != nullptr) {
			delete payload;
			payload = nullptr;
		}
	}
};



class ConvoyerItemPool
{
private:
	static inline ConvoyerItemPool* singleton;
	std::queue<ConvoyerItem*>* available = nullptr;

private:
	ConvoyerItemPool()
	{
		singleton = this;
		available = new std::queue<ConvoyerItem*>();
		for (unsigned int i = 0; i < C::CONVOYER_ITEM_POOL_SIZE; ++i)
			available->emplace(new ConvoyerItem());
	}

	~ConvoyerItemPool()
	{
		// Delete Available Items
		while (!available->empty()) {
			delete available->front();
			available->pop();
		}
		delete available;
	}



public:
	// For Setup only !!
	static void init() { singleton = new ConvoyerItemPool(); }
	// For Setup only !!
	static void release() { delete singleton; singleton = nullptr; }

public:
	static void free(ConvoyerItem* item)
	{
		item->payload = nullptr;
		if (singleton == nullptr) delete item;
		else singleton->freeInternal(item);
	}

	static ConvoyerItem* get(PayloadBase* payload)
	{
		// Get / Create item
		ConvoyerItem* item;
		if (singleton == nullptr) item = new ConvoyerItem();
		else item = singleton->getInternal();

		// Set Settings
		item->payload = payload;
		item->progression = 0.0f;
		item->pos.x = 0.0f;
		item->pos.y = 0.0f;

		// Return Item
		return item;
	}



private:
	ConvoyerItem* getInternal()
	{
		// Get a pool Item if possible, otherwise allocate it
		if (available->empty()) return new ConvoyerItem();
		ConvoyerItem* item = available->front();
		available->pop();
		return item;
	}

	void freeInternal(ConvoyerItem* item)
	{
		// Free item whatever
		if (item->pool) available->emplace(item);
		else delete item;
	}
};