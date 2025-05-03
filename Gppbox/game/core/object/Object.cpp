#include <imgui.h>
#include "Object.hpp"
#include "Collider.hpp"
#include "Rigidbody.hpp"
#include "engine/Utils.hpp"
#include "engine/utils/ScaleHelper.hpp"
#include "game/components/Component.hpp"

Object::Object()
{
	components = new std::vector<Component*>();
}

Object::~Object()
{
	LOOPF_C(delete c);
	delete components;
	if (rigidbody != nullptr) delete rigidbody;
	else if (collider != nullptr) delete collider;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Object::addComponent(Component* component)
{
	if (component == nullptr) return;
	this->components->push_back(component);
}

void Object::addComponents(Component** components, int componentCount)
{
	if (components == nullptr || componentCount <= 0) return;
	this->components->insert(this->components->end(), components, components + componentCount);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Object::preupdate(double dt)
{
	LOOPF_C(c->preupdate(dt));
}

void Object::fixed(double fdt)
{
	if (rigidbody != nullptr) rigidbody->processMovement(fdt);
	LOOPF_C(c->fixed(fdt));
}

void Object::update(double dt)
{
	LOOPB_C(c->update(dt));
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void Object::applyTransform(sf::RenderStates& states) const
{
	states.transform *= getTransform();
	states.transform *= ScaleHelper::invert();
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	drawInternal(target, states);
}

void Object::drawInternal(sf::RenderTarget& target, sf::RenderStates states) const
{
	applyTransform(states);
	LOOPF_C(target.draw(*c, states));
}

void Object::imgui()
{
	using namespace ImGui;

	// Draw components imgui
	LOOPF_C(c->imgui());
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool Object::isCollision(Object* other) const
{
	FULL_CHECK(other, this->isCollision(xpos, (int)ypos));
}

bool Object::isCollision(int gridx, int gridy) const
{
	return Utils::isFullBody(this, gridx, gridy);
}

std::vector<sf::Vector2i> Object::getCollisions() const
{
	std::vector<sf::Vector2i> collisions = std::vector<sf::Vector2i>();
	FULL_COLLISION(this, return collisions, collisions.emplace_back((int)xpos, (int)ypos));
	return collisions;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////