#include "EnnemyController.hpp"
#include "game/core/Entity.hpp"
#include "app/C.hpp"

EnnemyController::EnnemyController(Entity* entity) : Component(entity) { }


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void EnnemyController::preupdate(double dt) { }

void EnnemyController::fixed(double fdt)
{
	// Continuously update force to Ennemy
	entity->setDx(entity->dx + direction * entity->speed * fdt);
	if (entity->dx != 0.0f) entity->dirx = entity->dx < 0.0f ? -1 : 1;
}

void EnnemyController::update(double dt)
{
	// Invert Movement if collision detected
	if (entity->hcollision != 0) {
		direction = -entity->hcollision;
		entity->setDx(-entity->dx);
	}
}

void EnnemyController::imgui() { }


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool EnnemyController::canJump() { return false; }
