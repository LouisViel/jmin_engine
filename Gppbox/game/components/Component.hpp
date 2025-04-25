#pragma once

#include <SFML/Graphics.hpp>

class Object;

class Component : public sf::Drawable
{
protected:
	Object* gameobject;

public:
	Component() = delete;
	Component(Object* _object) : gameobject(_object) { }
	virtual ~Component() { }

	virtual void preupdate(double dt) { } // Pre Update (called even in "edit mode")
	virtual void fixed(double fdt) { } // Fixed Update (no call in "edit mode")
	virtual void update(double dt) { } // Update (no call in "edit mode")
	virtual void draw(sf::RenderTarget& win) { } // Graphics Drawing
	virtual void imgui() { } // Imgui Drawing

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { }
};