#pragma once
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
};

