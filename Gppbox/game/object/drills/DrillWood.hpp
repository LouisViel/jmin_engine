#pragma once
#include "Drill.hpp"

class DrillWood : public Drill<Payload>
{
public:
	DrillWood();
	virtual ~DrillWood();

private:
	//void performDrill() override;
};