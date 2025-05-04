#pragma once

enum class Direction : int
{
	Unknown = 0,
	North = 1 << 1,
	East = 1 << 2,
	South = 1 << 3,
	Weast = 1 << 4
};

constexpr inline Direction operator|(Direction a, Direction b)
{
	return static_cast<Direction>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr inline Direction operator&(Direction a, Direction b)
{
	return static_cast<Direction>(static_cast<int>(a) & static_cast<int>(b));
}

constexpr inline Direction operator+(Direction a, Direction b)
{
	return static_cast<Direction>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr inline Direction operator-(Direction a, Direction b)
{
	return static_cast<Direction>(static_cast<int>(a) & ~static_cast<int>(b));
}

constexpr inline bool operator==(Direction a, Direction b)
{
	return static_cast<int>(a) == static_cast<int>(b);
}

constexpr inline bool operator!=(Direction a, Direction b)
{
	return static_cast<int>(a) != static_cast<int>(b);
}

class DirectionHelper
{
public:
	static const Direction All = Direction::North | Direction::East | Direction::South | Direction::Weast;

	static bool has(Direction a, Direction b)
	{
		return (a & b) != Direction::Unknown;
	}

	static Direction connect(Direction dir)
	{
		if (dir == All) return dir;
		return DirectionHelper::inverse(dir);
	}

	static Direction inverse(Direction dir)
	{
		// Special Cases
		if (dir == All) return Direction::Unknown;
		if (dir == Direction::Unknown) return All;

		// Classic Cases
		Direction result = Direction::Unknown;
		if (dir == Direction::North) result = result | Direction::South;
		if (dir == Direction::East) result = result | Direction::Weast;
		if (dir == Direction::South) result = result | Direction::North;
		if (dir == Direction::Weast) result = result | Direction::East;
		return result;
	}
};