#include "game/object/Building.hpp"
#include "game/core/utils/ResourceType.hpp"

class ContainerBase : public Building
{
protected:
	int ressourceCount = 0;
	ResourceType type = ResourceType::Unknown;

public:
	ContainerBase(ResourceType type);
	virtual ~ContainerBase();
	int getCount() const { return ressourceCount; }
};