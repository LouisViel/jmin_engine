#include "Building.hpp"


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