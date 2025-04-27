#pragma once

#include <SFML/Graphics.hpp>
#include "game/core/utils/NodeType.hpp"
#include "game/core/utils/ResourceType.hpp"
#include "game/core/utils/Direction.hpp"

struct InOutConvoy
{
public:
	enum Mode {
		None = 0,
		In = 1,
		Out = 2,
	};

	sf::Vector2i anchor = sf::Vector2i(0, 0);
	InOutConvoy::Mode mode = Mode::None;
	ResourceType type = ResourceType::Unknown;
	Direction dir = Direction::Unknown;


	InOutConvoy(InOutConvoy::Mode mode, ResourceType type, Direction dir)
	{
		this->mode = mode;
		this->type = type;
		this->dir = dir;
	}

	InOutConvoy(InOutConvoy::Mode mode, ResourceType type, Direction dir, sf::Vector2i anchor)
	{
		this->anchor = anchor;
		this->mode = mode;
		this->type = type;
		this->dir = dir;
	}


	bool connect(InOutConvoy other) const
	{
		if (!ModeHelper::connect(this->mode, other.mode)) return false;
		Direction _dir = DirectionHelper::inverse(other.dir);
		return this->match(other.type, _dir);
	}

	bool connect(Mode mode, ResourceType type, Direction dir) const
	{
		if (!ModeHelper::connect(this->mode, mode)) return false;
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


private:
	class ModeHelper
	{
	public:
		static Mode inverse(Mode mode)
		{
			if (mode == Mode::In) return Mode::Out;
			if (mode == Mode::Out) return Mode::In;
			return Mode::None;
		}

		static bool connect(Mode a, Mode b)
		{
			return inverse(a) == b && b != Mode::None;
		}
	};
};
