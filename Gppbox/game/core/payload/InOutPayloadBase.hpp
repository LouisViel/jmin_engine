#pragma once
#include <queue>
#include "Payload.hpp"

class InOutPayloadBase
{
protected:
	std::queue<PayloadBase*>* payload = nullptr;
	size_t maxSize;

public:
	bool locked = false;

public:
	InOutPayloadBase();
	InOutPayloadBase(size_t maxSize);
	virtual ~InOutPayloadBase();

	bool valid() const;
	bool invalid() const;
	bool canPush() const;
	void empty();
};