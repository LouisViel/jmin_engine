#include "Building.hpp"
#include "engine/Utils.hpp"
#include "engine/utils/TransformHelper.hpp"
#include "game/core/utils/SpriteHelper.hpp"


Building::Building()
{
	inConvoys = new std::vector<InOutConvoy*>();
	outConvoys = new std::vector<InOutConvoy*>();
}

Building::~Building()
{
	for (InOutConvoy* const io : *inConvoys) delete io;
	delete inConvoys;
	for (InOutConvoy* const io : *outConvoys) delete io;
	delete outConvoys;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Building::addInput(InOutConvoy* const input)
{
	input->mode = InOutConvoy::Mode::In;
	inConvoys->push_back(input);
}

void Building::addOutput(InOutConvoy* const output)
{
	output->mode = InOutConvoy::Mode::Out;
	outConvoys->push_back(output);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Building::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Object::drawInternal(target, states);
	Object::applyTransform(states);

	sf::Transform transform = states.transform;
	TransformHelper helper = TransformHelper();
	sf::Drawable* drawable;

	for (InOutConvoy* convoy : *inConvoys) {
		sf::Vector2i anchorPos = convoy->anchor;
		if (anchorPos.y <= 0) {
			drawable = SpriteHelper::get(SpriteStatic::ConvoyInput_Down);
			anchorPos.y -= 1;
		} else {
			drawable = SpriteHelper::get(SpriteStatic::ConvoyInput_Up);
			anchorPos.y += 1;
		}
		helper.setPosition((float)anchorPos.x, (float)anchorPos.y);
		states.transform = transform * helper.getTransform();
		target.draw(*drawable, states);
	}

	for (InOutConvoy* convoy : *outConvoys) {
		sf::Vector2i anchorPos = convoy->anchor;
		if (anchorPos.y <= 0) {
			drawable = SpriteHelper::get(SpriteStatic::ConvoyOutput_Up);
			anchorPos.y -= 1;
		} else {
			drawable = SpriteHelper::get(SpriteStatic::ConvoyOutput_Down);
			anchorPos.y += 1;
		}
		helper.setPosition((float)anchorPos.x, (float)anchorPos.y);
		states.transform = transform * helper.getTransform();
		target.draw(*drawable, states);
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


InOutConvoy* Building::getInput(sf::Vector2i gridPos, InOutConvoy* inOutConvoy) const
{
	// Setup process settings
	sf::Vector2f pos = this->getPosition();
	sf::Vector2i position = sf::Vector2i((int)pos.x, (int)pos.y);
	sf::Vector2i anchorPos = gridPos + inOutConvoy->anchor;
	
	// Loop over & check if convoys connects
	InOutConvoy& convoy = *inOutConvoy;
	for (InOutConvoy* inConvoy : *inConvoys) {
		if (inConvoy->connect(convoy)) {

			// if connects, check if are adjacents/fully valids
			sf::Vector2i inPos = position + inConvoy->anchor;
			if (Utils::isAdjacent(anchorPos, inPos) || anchorPos == inPos) {
				inConvoy->worldPos = position;
				return inConvoy;
			}
		}
	}

	// No input valid founded
	return nullptr;
}

InOutConvoy* Building::getOutput(sf::Vector2i gridPos, InOutConvoy* inOutConvoy) const
{
	sf::Vector2f pos = this->getPosition();
	sf::Vector2i position = sf::Vector2i((int)pos.x, (int)pos.y);
	sf::Vector2i anchorPos = gridPos + inOutConvoy->anchor;

	// Loop over & check if convoys connects
	InOutConvoy& convoy = *inOutConvoy;
	for (InOutConvoy* outConvoy : *outConvoys) {
		if (outConvoy->connect(convoy)) {

			// if connects, check if are adjacents/fully valids
			sf::Vector2i inPos = position + outConvoy->anchor;
			if (Utils::isAdjacent(anchorPos, inPos) || anchorPos == inPos) {
				outConvoy->worldPos = position;
				return outConvoy;
			}
		}
	}

	// No input valid founded
	return nullptr;
}