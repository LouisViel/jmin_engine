#pragma once
#include "Drill.hpp"

class DrillWood : public Drill<Payload>
{
public:
	DrillWood();
	virtual ~DrillWood();

protected:
	Payload* getPayload() override;
};