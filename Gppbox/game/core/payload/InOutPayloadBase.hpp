#pragma once
#include <queue>
#include "Payload.hpp"

class InOutPayloadBase
{
protected:
	std::queue<PayloadBase*>* payload = nullptr;
	size_t maxSize;
	int linkedCount = 0;

public:
	bool locked = false;
	bool closing = false;

public:
	InOutPayloadBase();
	InOutPayloadBase(size_t maxSize);
	virtual ~InOutPayloadBase();

	void link();
	void unlink();

	bool valid() const;
	bool invalid() const;
	bool canPush() const;
	void empty();
};