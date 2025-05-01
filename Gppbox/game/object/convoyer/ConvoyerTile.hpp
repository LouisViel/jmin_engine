#pragma once

enum class ConvoyerTile : int
{
	// Empty Tile (last one)
	Empty = (10 * 9) - 1,
	Invalid = (10 * 9) - 2,

	// Right Tiles
	Right = 0, // 0 -> 3
	RightTop = 61, // 60 -> 63
	RightDown = 72, // 72 -> 75
	RightStart = 16, // 16 -> 19
	RightEnd = 20, // 20 -> 23

	// Left Tiles
	Left = 4, // 4 -> 7
	LeftTop = 48, // 48 -> 51
	LeftDown = 68, // 68 -> 71
	LeftStart = 28, // 28 -> 31
	LeftEnd = 24, // 24 -> 27

	// Top Tiles
	Top = 12, // 12 -> 15
	TopRight = 64, // 64 -> 67
	TopLeft = 76, // 76 -> 79
	TopStart = 44, // 44 -> 47
	TopEnd = 36, // 36 -> 39

	// Down Tiles
	Down = 8, // 8 -> 11
	DownRight = 52, // 52 -> 55
	DownLeft = 56, // 56 -> 59
	DownStart = 32, // 32 -> 35
	DownEnd = 40, // 40 -> 43

	// Bonus Tiles : Speed
	SpeedTop = 80,
	SpeedDown = 81,
	SpeedLeft = 82,
	SpeedRight = 83,

	// Bonus Tiles : Lights
	LightBlue = 84,
	LightRed = 85,
	LightGreen = 86,
};

constexpr inline int operator&(ConvoyerTile tile)
{
	return static_cast<int>(tile);
}