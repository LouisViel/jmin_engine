#pragma once
#include "Crafter.hpp"

typedef Payload CrafterPlanksPayload;
typedef Payload CrafterPlanksPayloadOutput;

class CrafterPlanks : public Crafter<CrafterPlanksPayloadOutput>
{
private:
	InOutConvoyHandle<CrafterPlanksPayload>* inputHandle = nullptr;
	int craftNeededWoodCount = 5;
	int inputWoodCount = 0;

public:
	CrafterPlanks();
	virtual ~CrafterPlanks();

	void update(double dt) override;
	void craftPerformed() override;
	CrafterPlanksPayloadOutput* getPayload() override;
};
