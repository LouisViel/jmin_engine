#pragma once

#include <queue>

template <typename t>
class InOutPayload
{
private:
	std::queue<t*>* payload = nullptr;
	size_t maxSize;

public:
	InOutPayload(size_t maxSize);
	~InOutPayload();

	bool valid() const;
	bool invalid() const;

	t* pop();
	bool push(t* elem);

	void empty();
	std::vector<t*>* toVector(bool flush = true);
};
