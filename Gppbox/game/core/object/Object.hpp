#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "app/M.hpp"

class Component;
class Collider;
class Rigidbody;

class Object : public sf::Drawable, public sf::Transformable
{
private:
	// Loop Forward on components
	#define LOOPF_C(action) \
		LOOPF_PTR(components, Component* c) \
		action; \
		LOOP_END

	// Loop Backward on components
	#define LOOPB_C(action) \
		LOOPB_PTR(components, Component* c) \
		action; \
		LOOP_END

private:
	std::vector<Component*>* components = nullptr;

public:
	Rigidbody* rigidbody = nullptr;
	Collider* collider = nullptr;

public:
	Object();
	~Object();

	void addComponent(Component* component); // Add one component
	void addComponents(Component** components, int componentCount); // Add multiple components

	void preupdate(double dt); // Pre Update Object
	void fixed(double fdt); // Fixed Update Object
	void update(double dt); // Update Object
	void draw(sf::RenderTarget& win); // Graphics Drawing
	void imgui(); // Imgui Drawing

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
