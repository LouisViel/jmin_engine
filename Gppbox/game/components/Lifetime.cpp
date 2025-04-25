#include "Lifetime.hpp"
#include "game/core/Game.hpp"
#include "game/core/World.hpp"

Lifetime::Lifetime(Object* object, float _lifetime) : Component(object), lifetime(_lifetime) { }

void Lifetime::preupdate(double dt)
{
	lifetime -= (float)dt;
	if (lifetime <= 0.0f) {
		Game::singleton->world->removeObject(nullptr, gameobject);
	}
}