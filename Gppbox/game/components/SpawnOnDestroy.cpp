#include "SpawnOnDestroy.hpp"
#include "Lifetime.hpp"

#include "game/core/Game.hpp"
#include "game/core/World.hpp"
#include "game/core/object/Object.hpp"


SpawnOnDestroy::SpawnOnDestroy(Object* object) : Component(object) { }

SpawnOnDestroy::~SpawnOnDestroy()
{
	if (Game::singleton == nullptr) return;

	bool isShape = textureSize != sf::Vector2f{ 0, 0 };
	bool isTexture = texture.length() > 0;
	bool isLifetime = lifetime > 0.0f;

	// Generate Sprite if added
	sf::RectangleShape* spr = nullptr;
	if (isShape) spr = new sf::RectangleShape(textureSize);

	// Generate Object
	//Object* e = new Object(spr);
	//sf::Vector2i coo = object->getPosPixel();
	//e->setCooPixel(coo.x, coo.y);
	//e->syncPos();

	//e->sheight = sheight;
	//e->swidth = swidth;
	//e->lifepoints = lifepoints;

	//e->frx = frx;
	//e->fry = fry;
	//e->usePhysics = usePhysics;
	//e->gravy = gravy;

	//// Inject Sprite with Texture if added
	//if (isShape && isTexture) e->addComponent(new SpriteOverride(e, texture));

	//// Inject Lifetime destroyer
	//if (isLifetime) e->addComponent(new Lifetime(e, lifetime));

	//// Register Object into pool
	//Game::singleton->world->gameobjects->push_back(e);
}