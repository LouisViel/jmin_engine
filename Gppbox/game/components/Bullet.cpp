#include "Bullet.hpp"
#include "game/core/Game.hpp"
#include "game/core/World.hpp"
#include "game/core/object/Object.hpp"
#include "game/core/object/Collider.hpp"

Bullet::Bullet(Object* object) : Component(object) { }

Bullet::Bullet(Object* object, float _damages) : Component(object), damages(_damages) { }

void Bullet::fixed(double fdt)
{
	Game* g = Game::singleton;
	World* w = g->world;

	// Check if oustide world bounds
	Collider* col = gameobject->collider;
	/*if (g->isBorderX((float)col->cx) || g->isBorderY((float)col->cy) || g->isWall(col->cx, col->cy)) {
		w->removeObject(nullptr, gameobject);
		return;
	}*/

	// Check if hit an ennemy
	/*Object* ennemy = w->getEnnemy(col->cx, col->cy);
	if (ennemy != nullptr && ennemy->lifepoints > 0.0f) {
		ennemy->lifepoints -= damages;
		if (ennemy->lifepoints <= 0.0f) w->removeEnnemy(ennemy);
		w->removeObject(nullptr, gameobject);
		return;
	}*/
}