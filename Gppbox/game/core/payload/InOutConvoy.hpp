#pragma once
#include <SFML/Graphics.hpp>
#include "game/core/utils/NodeType.hpp"
#include "game/core/utils/ResourceType.hpp"
#include "game/core/utils/Direction.hpp"
#include "InOutPayload.hpp"

// Declare Advanced Handle existence
template <typename t>
class InOutConvoyHandle;


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


class InOutConvoy
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

	virtual ~InOutConvoy() { return; }


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


	template <typename t>
	InOutConvoyHandle<t>* handle()
	{
		return static_cast<InOutConvoyHandle<t>*>(this);
	}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


private:
	class ModeHelper
	{
	public:
		static Mode inverse(Mode mode) {
			if (mode == Mode::In) return Mode::Out;
			if (mode == Mode::Out) return Mode::In;
			return Mode::None;
		}

		static bool connect(Mode a, Mode b) {
			return inverse(a) == b && b != Mode::None;
		}
	};
};


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


template <typename t>
class InOutConvoyHandle : public InOutConvoy
{
public:
	bool managePayload = false;
	InOutPayload<t>* payload = nullptr;


	InOutConvoyHandle() = delete;

	InOutConvoyHandle(InOutConvoy::Mode mode, ResourceType type, Direction dir)
		: InOutConvoy(mode, type, dir) { }

	InOutConvoyHandle(InOutConvoy::Mode mode, ResourceType type, Direction dir, sf::Vector2i anchor)
		: InOutConvoy(mode, type, dir, anchor) { }

	virtual ~InOutConvoyHandle()
	{
		if (managePayload) {
			delete payload;
		}
	}


	InOutConvoy* boxed()
	{
		return static_cast<InOutConvoy*>(this);
	}
};

typedef InOutConvoyHandle<PayloadBase> InOutConvoyDefault;