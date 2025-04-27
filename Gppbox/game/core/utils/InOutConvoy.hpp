#pragma once

#include "game/core/utils/NodeType.hpp"
#include "game/core/utils/ResourceType.hpp"
#include "game/core/utils/Direction.hpp"

struct InOutConvoy
{
public:
	ResourceType type = ResourceType::Unknown;
	Direction dir = Direction::Unknown;

	InOutConvoy(ResourceType type, Direction dir)
	{
		this->type = type;
		this->dir = dir;
	}

	bool connect(InOutConvoy other) const
	{
		Direction _dir = DirectionHelper::inverse(other.dir);
		return this->match(other.type, _dir);
	}

	bool connect(ResourceType type, Direction dir) const
	{
		Direction _dir = DirectionHelper::inverse(dir);
		return this->match(type, _dir);
	}

	bool match(InOutConvoy other) const
	{
		return ResourceTypeHelper::has(this->type, other.type) &&
			DirectionHelper::has(this->dir, other.dir);
	}

	bool match(ResourceType type, Direction dir) const
	{
		return ResourceTypeHelper::has(this->type, type) &&
			DirectionHelper::has(this->dir, dir);
	}
};
