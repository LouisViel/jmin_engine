#include "imgui.h"
#include "World.hpp"

#include "game/core/object/Object.hpp"
#include "game/components/PlayerController.hpp"

#include "engine/utils/ScaleHelper.hpp"
#include "engine/Utils.hpp"
#include "app/C.hpp"


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


World::World(sf::RenderWindow* win)
{
	gameobjects = new std::vector<Object*>();

	buildings = new std::vector<Building*>();
	convoyers = new std::vector<Convoyer*>();
	details = new std::vector<Object*>();

	// Insert Player Creation
	// Insert "Bonus" Creation

	initMainChar();
	initPetDrone();
}

World::~World()
{
	for (Object* e : *gameobjects) delete e;
	delete gameobjects;

	// Voir si on delete pas en plus le contenu de ces vectors
	for (Building* b : *buildings) delete b;
	for (Convoyer* c : *convoyers) delete c;
	for (Object* d : *details) delete d;
	delete buildings;
	delete convoyers;
	delete details;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void World::preupdate(double dt)
{
	LOOPF_E(e->preupdate(dt));
}

void World::fixed(double fdt)
{
	LOOPF_E(e->fixed(fdt));
}


void World::update(double dt)
{
	LOOPF_E(e->update(dt));
}

void World::processDelete()
{
	if (toDelete.size() <= 0) return;
	std::unordered_set<Object*> cdelete = toDelete;
	toDelete.clear();
	for (Object* e : cdelete) {
		REMOVE_ITEM(Object*, gameobjects, e);
		delete e;
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void World::draw(sf::RenderTarget& win)
{
	sf::RenderStates states = sf::RenderStates::Default;
	states.transform *= ScaleHelper::apply();
	LOOPF_E(win.draw(*e, states));
}

void World::imgui()
{
	using namespace ImGui;
	
	if (TreeNodeEx("Gameobjects", 0)) {
		Indent(5.0f);
		LOOPF_PTR(gameobjects, Object* e);
		std::string txt = ("Object " + std::to_string(i));
		if (TreeNodeEx(txt.c_str())) {
			e->imgui();
			TreePop();
		}
		LOOP_END;
		TreePop();
	}

	if (TreeNodeEx("Buildings", 0)) {
		Indent(5.0f);

		// TODO : Mettre les bouttons pour les différents Buildings

		if (TreeNodeEx("Wood", 0)) {

			TreePop();
		}

		if (TreeNodeEx("Stone", 0)) {

			TreePop();
		}

		/*if (TreeNodeEx("Coal", 0)) {

			TreePop();
		}*/

		if (TreeNodeEx("Iron", 0)) {

			TreePop();
		}

		TreePop();
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void World::initMainChar() {
	//// Create Player Sprite
	//sf::RectangleShape* spr = new sf::RectangleShape({ C::GRID_SIZE * C::S_SCALER_X, C::GRID_SIZE * 2 * C::S_SCALER_Y });
	//spr->setFillColor(sf::Color::Magenta);
	//spr->setOutlineColor(sf::Color::Red);
	//spr->setOutlineThickness(2);
	//spr->setOrigin({ C::GRID_SIZE * 0.5f, C::GRID_SIZE * 2 });

	//// Create Player with "default" settings
	//Object* e = new Object(spr);
	//e->setCooGrid(3, int(C::RES_Y / C::GRID_SIZE) - 4 + 0.99f);
	//e->syncPos();

	//// Inject Custom Player Settings
	//e->sheight = C::P_HEIGHT;
	//e->swidth = C::P_WIDTH;
	//e->lifepoints = C::P_LIFEPOINTS;
	//e->speed = C::P_SPEED;
	////e->jumpforce = C::P_JUMP;
	//e->dirx = 1;

	//// Add components
	//e->addComponent(new PlayerController(e));
	//e->addComponent(new SpriteOverride(e, "res/player.png"));

	//// Register Player
	//gameobjects->push_back(e);
	//printf("player added\n");
}

void World::initPetDrone()
{
	//constexpr float sizeX = 0.5f;
	//constexpr float sizeY = 0.5f;

	//// Create Drone Sprite
	//sf::RectangleShape* spr = new sf::RectangleShape({ C::GRID_SIZE * sizeX * 1.75f, C::GRID_SIZE * sizeY * 1.75f });
	//spr->setFillColor(sf::Color::Green);
	//spr->setOutlineColor(sf::Color::Yellow);
	//spr->setOutlineThickness(1);

	//// Create Drone with "default" settings
	//Object* e = new Object(spr);
	//e->setCooGrid(3, int(C::RES_Y / C::GRID_SIZE) - 4 + 0.99f);
	//e->syncPos();

	//// Inject Drone Settings
	//e->sheight = sizeX;
	//e->swidth = sizeY;
	////e->speed = C::P_DRONE;
	////e->jumpforce = C::P_DRONE;
	//e->fry = e->frx;
	//e->gravy = 0.0f;

	//// Add components
	//e->addComponent(new SpriteOverride(e, "res/drone.png"));
	//e->spr->setFillColor(sf::Color::Cyan);

	//// Register Drone
	//gameobjects->push_back(e);
	//printf("drone added\n");
}

Object* World::initEnnemy(float x, float y)
{
	return nullptr;
//	Object* e = initEnnemyCore(x, y);
//	//e->addComponent(new EnnemyController(e));
//	gameobjects->push_back(e);
//	//ennemies->push_back(e);
//	return e;
}

Object* World::initEnnemyCore(float x, float y)
{
	return nullptr;
//	// Create Ennemy Sprite
//	sf::RectangleShape* spr = new sf::RectangleShape({ C::GRID_SIZE * C::S_SCALER_X, C::GRID_SIZE * 2 * C::S_SCALER_Y });
//	spr->setFillColor(sf::Color::Yellow);
//	spr->setOutlineColor(sf::Color::Red);
//	spr->setOutlineThickness(2);
//	spr->setOrigin({ C::GRID_SIZE * 0.5f, C::GRID_SIZE * 2 });
//
//	// Create Ennemy with "default" settings
//	Object* e = new Object(spr);
//	e->setCooGrid(x, y);
//	e->syncPos();
//
//	// Inject Custom Ennemy Settings
//	e->sheight = C::P_HEIGHT;
//	e->swidth = C::P_WIDTH;
//	e->lifepoints = C::E_LIFEPOINTS;
//	e->speed = C::P_SPEED;
//	//e->jumpforce = C::P_JUMP;
//
//	// Add Override Sprite
//	e->addComponent(new SpriteOverride(e, "res/ennemy.png"));
//
//	return e;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void World::removeEnnemy(Object* ennemy)
{
	//this->removeObject(this->ennemies, ennemy);
}

void World::removeObject(std::vector<Object*>* quick, Object* object)
{
	if (quick != nullptr) { REMOVE_ITEM(Object*, quick, object); }
	toDelete.emplace(object);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


Object* World::getPlayer()
{
	if (gameobjects->size()) return gameobjects->operator[](0);
	return nullptr;
}

Object* World::getEnnemy(int gridx, int gridy)
{
	/*for (Object* e : *ennemies) {
		if (Utils::isFullBody(e, gridx, gridy)) return e;
	}*/
	return nullptr;
}

std::set<Object*> World::getEnnemies(int gridx, int gridy)
{
	std::set<Object*> results = std::set<Object*>();
	/*for (Object* e : *ennemies) {
		if (Utils::isFullBody(e, gridx, gridy)) {
			results.emplace(e);
		}
	}*/
	return results;
}

Object* World::getClosest(std::vector<Object*>* vector, sf::Vector2i posPix)
{
	Object* target = nullptr;
	float distance = INFINITY;

	for (Object* e : *vector) {
		sf::Vector2i eposPix = sf::Vector2i(0, 0); //e->getPosition();// e->getPosPixel();
		float dist = Utils::toLength(eposPix - posPix);
		if (dist < distance) {
			distance = dist;
			target = e;
		}
	}

	return target;
}

bool World::isValid(std::vector<Object*>* vector, Object* object)
{
	if (object == nullptr) return false;
	for (Object* e : *vector) {
		if (e == object)
			return true;
	}
	return false;
}