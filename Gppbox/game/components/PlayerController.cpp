#include "PlayerController.hpp"
#include "engine/utils/InputHandler.hpp"
#include "game/core/object/Object.hpp"
#include "game/core/object/Rigidbody.hpp"
#include "app/M.hpp"

PlayerController::PlayerController(Object* object) : Component(object) { }


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void PlayerController::preupdate(double dt)
{
	// No logistic Update
	NO_UPDATE(dt);
	processInputs(dt);

	// Update Jump Delay Timer
	if (jumpDelay > 0.0f) {
		jumpDelay -= (float)dt;
	}
}

void PlayerController::fixed(double fdt) { }

void PlayerController::update(double dt) { }

void PlayerController::imgui() { }


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void PlayerController::processInputs(double dt)
{
	// Check for game window Focus + Imgui not overriding it
	if (!InputHandler::hasFocus()) return;
	if (!InputHandler::canUse()) return;

	// Get & Apply Horizontal Movement
	sf::Vector2f hor = InputHandler::getHorizontal();
	Rigidbody* const rb = gameobject->rigidbody;
	if (hor.x > 0.5f) rb->setDx(rb->dx - rb->speed * dt * hor.x);
	else if (hor.y > 0.5f) rb->setDx(rb->dx + rb->speed * dt * hor.y);

	// Get & Apply Jump
	/*if (InputHandler::getJump()) {
		object->setJumping(true);
	}*/
}
