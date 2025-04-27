#pragma once

#include "game/core/object/Object.hpp"
#include "game/core/utils/InOutConvoy.hpp"

class Building : public Object
{
private:
	std::vector<InOutConvoy>* inConvoys = nullptr;
	std::vector<InOutConvoy>* outConvoys = nullptr;

public:
	Building();
	~Building();
};
