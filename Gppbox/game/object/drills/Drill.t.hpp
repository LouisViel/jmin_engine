#pragma once
#include "game/object/Building.hpp"
#include "app/C.hpp"

template <typename t>
class Drill : public Building
{
protected:
	InOutConvoyHandle<t>* outputHandle = nullptr;

public:
	Drill();
	Drill(size_t maxPayload);
	virtual ~Drill() { return }
};
