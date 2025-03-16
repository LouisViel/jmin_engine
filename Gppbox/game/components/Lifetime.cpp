#include "Lifetime.hpp"
#include "game/core/Game.hpp"
#include "game/core/World.hpp"

Lifetime::Lifetime(Entity* entity, float _lifetime) : Component(entity), lifetime(_lifetime) { }

void Lifetime::preupdate(double dt)
{
	lifetime -= dt;
	if (lifetime <= 0.0f) {
		Game::singleton->world->removeEntity(nullptr, entity);
	}
}