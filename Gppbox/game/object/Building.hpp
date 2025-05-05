#pragma once
#include "game/core/object/Object.hpp"
#include "game/core/payload/InOutConvoy.hpp"
#include "game/core/payload/PayloadPool.hpp"
#include "game/core/payload/Payload.hpp"
#include "game/components/Renderer.hpp"
#include "engine/Utils.hpp"
#include "app/C.hpp"

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

	InOutConvoy* getInput(sf::Vector2i gridPos, InOutConvoy* inOutConvoy) const;
	InOutConvoy* getOutput(sf::Vector2i gridPos, InOutConvoy* inOutConvoy) const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void configure() { }
};
