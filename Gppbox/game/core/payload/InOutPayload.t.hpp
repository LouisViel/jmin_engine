#pragma once
#include "InOutPayloadBase.hpp"

template <typename t>
class InOutPayload : public InOutPayloadBase
{
public:
	using InOutPayloadBase::InOutPayloadBase;
	bool push(t* elem);
	t* pop();
	std::vector<t*>* toVector(bool flush = true);
};

typedef InOutPayload<PayloadBase> InOutPayloadDefault;
