#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "app/M.hpp"

class Component;
class Collider;
class Rigidbody;

class Object : public sf::Drawable, public sf::Transformable
{
protected:
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

protected:
	std::vector<Component*>* components = nullptr;

public:
	Rigidbody* rigidbody = nullptr;
	Collider* collider = nullptr;

public:
	Object();
	virtual ~Object();

	void addComponent(Component* component); // Add one component
	void addComponents(Component** components, int componentCount); // Add multiple components

	virtual void preupdate(double dt); // Pre Update Object
	virtual void fixed(double fdt); // Fixed Update Object
	virtual void update(double dt); // Update Object
	virtual void imgui(); // Imgui Drawing

	virtual bool isCollision(Object* other) const;
	virtual bool isCollision(int gridx, int gridy) const;
	virtual std::vector<sf::Vector2i> getCollisions() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	virtual void drawInternal(sf::RenderTarget& target, sf::RenderStates states) const;
	void applyTransform(sf::RenderStates& states) const;
};
