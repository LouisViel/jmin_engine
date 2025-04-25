#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.hpp"

class Game;
class Object;

class Rigidbody : public Collider
{
private:
	Object* gameobject;
	int hcollision = 0; // Horizontal Collision : -1 = left, 0 = none, 1 = right
	int vcollision = 0; // Vertical Collision : -1 = bottom, 0 = none, 1 = top

public:
	// Global Settings
	bool autoPublish = true;
	bool usePhysics = true;
	float speed = 1.0f;

	// Friction Settings
	float frx = 0.84f;
	float fry = 0.84f;

	// Current Move Speed
	float dx = 0.0f;
	float dy = 0.0f;

public:
	Rigidbody() = delete;
	Rigidbody(Object* _object);

	void processMovement(double fdt); // Process Object Full Movement
	void publishTransform(); // Publish Transform to Object

	void setDx(double dx); // Set dx (using clamp)
	void setDy(double dy); // Set dy (using clamp)
	sf::Vector2i getCollision(); // Get Collision infos

private:
	void processHorizontal(Game& g, float& _rx, const float& _ry); // Internal Process Movement Horizontal
	void processVertical(Game& g, const float& _rx, float& _ry); // Internal Process Movement Vertical
};
