#pragma once
#include <SFML/System/Vector2.hpp>

class Collider
{
public:
	int	cx = 0; // Position "case" en x
	int	cy = 0; // Position "case" en y
	float rx = 0.5f; // Reste de position en x
	float ry = 0.0f; // Reste de position en y

public:
	// Collider Settings
	float height = 1.0f;
	float width = 1.0f;

	Collider() { }
	Collider(float width, float height) : width(width), height(height) { }
	Collider(sf::Vector2f size) : width(size.x), height(size.y) { }

	void sync(sf::Vector2f pos)
	{
		cx = (int)pos.x;
		cy = (int)pos.y;
		rx = pos.x - cx;
		ry = pos.y - cy;
	}

	void sync(sf::Vector2i pos)
	{
		cx = pos.x;
		cy = pos.y;
		rx = 0;
		ry = 0;
	}
};
