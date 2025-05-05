#include "CrafterPlanks.hpp"
#include "game/core/utils/RessourceSprite.hpp"
#include "app/C.hpp"

CrafterPlanks::CrafterPlanks() : Crafter(COLLIDER_SIZE_CRAFTER)
{
	// Set output settings
	outputHandle->type = ResourceType::Planks;
	outputHandle->anchor = sf::Vector2i(1, 0);

	// Create & set input settings
	inputHandle = new InOutConvoyHandle<CrafterPlanksPayload>(InOutConvoy::Mode::In, ResourceType::Wood, Direction::South);
	inputHandle->setPayload(new InOutPayload<CrafterPlanksPayload>(C::BUILDER_PAYLOAD), true);
	inputHandle->anchor = sf::Vector2i(1, 2);
	this->addInput(inputHandle->boxed());

	// Add Renderer
	Renderer* renderer = new Renderer(this, "assets/bdg/crafter_planks.png");
	renderer->setScale(COLLIDER_SIZE_CRAFTER);
	this->addComponent(renderer);
}

CrafterPlanks::~CrafterPlanks()
{
	return;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void CrafterPlanks::update(double dt)
{

	// Read/Update input buffer & input counts
	InOutPayloadDefault* payloadhandle = inputHandle->getPayload();
	while (payloadhandle->valid()) {
		CrafterPlanksPayload* payload = payloadhandle->pop();
		inputWoodCount = Utils::safeAdd(inputWoodCount, payload->quantity);
		PayloadPool::free(payload);
	}

	// Perform crafting if needed amount valid
	if (inputWoodCount >= craftNeededWoodCount) {
		Crafter::update(dt);
	}
}

void CrafterPlanks::craftPerformed()
{
	// Update wood amount available
	inputWoodCount = Utils::safeMinus(inputWoodCount, craftNeededWoodCount);
}

CrafterPlanksPayloadOutput* CrafterPlanks::getPayload()
{
	sf::Drawable* render = RessourceSprite::get(ResourceType::Planks);
	return PayloadPool::get(1, render);
}