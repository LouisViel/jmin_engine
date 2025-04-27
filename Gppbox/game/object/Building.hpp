#pragma once
#include "game/core/object/Object.hpp"
#include "game/core/payload/InOutConvoy.hpp"
#include "game/core/payload/PayloadPool.hpp"
#include "game/core/payload/Payload.hpp"

class Building : public Object
{
private:
	std::vector<InOutConvoy*>* inConvoys = nullptr;
	std::vector<InOutConvoy*>* outConvoys = nullptr;

public:
	NodeType nodeType = NodeType::None;

public:
	Building();
	virtual ~Building();

	void addInput(InOutConvoy* const input);
	void addOutput(InOutConvoy* const output);

private:
	virtual void configure() { }
};
