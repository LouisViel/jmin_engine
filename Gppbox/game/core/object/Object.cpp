#include <imgui.h>
#include "Object.hpp"
#include "Collider.hpp"
#include "Rigidbody.hpp"
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
	//hcollision = 0; // Reset Horizontal collision tag
	LOOPF_C(c->preupdate(dt));
}

void Object::fixed(double fdt)
{
	LOOPF_C(c->fixed(fdt));
	//processMovement(fdt);
}

void Object::update(double dt)
{
	LOOPB_C(c->update(dt));
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.transform *= ScaleHelper::invert();
	LOOPF_C(target.draw(*c, states));
}

void Object::imgui()
{
	using namespace ImGui;
	bool chg = false, chgCoo = false;

	/*Value("jumping", isJumping);
	Value("grounded", isGrounded);
	Value("cx", cx);
	Value("cy", cy);
	Value("rx", rx);
	Value("ry", ry);

	sf::Vector2i pix = getPosPixel();
	chg |= DragInt2("pix x/pix y", &pix.x, 1.0f, -2000, 2000);
	if (chg) setCooPixel(pix.x, pix.y);

	chg |= DragInt2("cx/cy", &cx, 1.0f, -2000, 2000);

	sf::Vector2f coo = { cx + rx, cy + ry };
	chgCoo = DragFloat2("coo grid x/y", &coo.x, 1.0f, -2000, 2000);
	if (chgCoo) setCooGrid(coo.x, coo.y);

	chg |= DragFloat2("dx/dy", &dx, 0.01f, -20, 20);
	chg |= DragFloat2("frx/fry", &frx, 0.001f, 0, 1);
	chg |= DragFloat("gravy/fry", &gravy, 0.001f, -2, 2);

	if (Button("reset")) {
		chg |= true;

		cx = 3;
		cy = 54;
		rx = 0.5f;
		ry = 0.99f;

		dx = dy = 0.0f;
		setGrounded(false);
		setJumping(false);
	}*/

	// Draw components imgui
	LOOPF_C(c->imgui());

	//return chg || chgCoo;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
