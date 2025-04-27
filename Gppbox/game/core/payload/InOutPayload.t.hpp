#pragma once
#include <queue>

template <typename t>
class InOutPayload
{
private:
	std::queue<t*>* payload = nullptr;
	size_t maxSize;

public:
	bool locked = false;

public:
	InOutPayload();
	InOutPayload(size_t maxSize);
	~InOutPayload();

	bool valid() const;
	bool invalid() const;
	bool canPush() const;

	t* pop();
	bool push(t* elem);

	void empty();
	std::vector<t*>* toVector(bool flush = true);
};
