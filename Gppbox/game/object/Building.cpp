#include "Building.hpp"
#include "engine/Utils.hpp"


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
			if (Utils::isAdjacent(anchorPos, inPos)) return inConvoy;
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
			if (Utils::isAdjacent(anchorPos, inPos)) {
				outConvoy->worldPos = position;
				return outConvoy;
			}
		}
	}

	// No input valid founded
	return nullptr;
}