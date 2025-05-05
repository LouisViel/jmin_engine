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
}

void PlayerController::update(double dt)
{
	NO_UPDATE(dt);

	const float sizeX = C::RES_X / (float)C::GRID_SIZE;
	const float sizeY = C::RES_Y / (float)C::GRID_SIZE;
	const float margeX = sizeX * 0.0f, margeY = sizeY * 0.0f;
	const float maxX = sizeX + margeX, maxY = sizeY + margeY;
	const float minX = -margeX, minY = -margeY;

	sf::Vector2f pos = gameobject->getPosition();
	pos.x = std::clamp(pos.x, minX, maxX);
	pos.y = std::clamp(pos.y, minY, maxY);
	gameobject->setPosition(pos);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void PlayerController::processInputs(double dt)
{
	// Check for game window Focus + Imgui not overriding it
	if (!InputHandler::hasFocus()) return;
	//if (!InputHandler::canUse()) return;
	Rigidbody* const rb = gameobject->rigidbody;

	// Get & Apply Horizontal Movement
	sf::Vector2f hor = InputHandler::getHorizontal();
	if (hor.x > 0.5f) rb->setDx(rb->dx - rb->speed * dt * hor.x);
	else if (hor.y > 0.5f) rb->setDx(rb->dx + rb->speed * dt * hor.y);

	// Get & Apply Vertical Movement
	sf::Vector2f vert = InputHandler::getVertical();
	if (vert.x > 0.5f) rb->setDy(rb->dy + rb->speed * dt * vert.x);
	else if (vert.y > 0.5f) rb->setDy(rb->dy - rb->speed * dt * vert.y);
}
