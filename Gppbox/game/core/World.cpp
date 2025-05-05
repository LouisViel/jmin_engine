#include "imgui.h"
#include "World.hpp"

#include "game/core/object/Object.hpp"
#include "game/components/PlayerController.hpp"
#include "game/core/object/Rigidbody.hpp"

#include "engine/utils/ScaleHelper.hpp"
#include "engine/Utils.hpp"
#include "app/C.hpp"


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


World::World(sf::RenderWindow* win)
{
	previews = new std::vector<Object*>();
	gameobjects = new std::vector<Object*>();

	buildings = new std::vector<Building*>();
	convoyers = new std::vector<Convoyer*>();
	details = new std::vector<Object*>();

	initPlayer();
	// Insert "Bonus" Creations
}

World::~World()
{
	for (Object* o : *previews) delete o;
	delete previews;
	for (Object* o : *gameobjects) delete o;
	delete gameobjects;
	delete buildings;
	delete convoyers;
	delete details;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void World::preupdate(double dt)
{
	LOOPB_O(previews, Object*, o->preupdate(dt));
	LOOPF_O(gameobjects, Object*, o->preupdate(dt));
	/*LOOPF_O(buildings, Building*, o->preupdate(dt));
	LOOPF_O(convoyers, Convoyer*, o->preupdate(dt));
	LOOPF_O(details, Object*, o->preupdate(dt));*/
}

void World::fixed(double fdt)
{
	LOOPB_O(previews, Object*, o->fixed(fdt));
	LOOPF_O(gameobjects, Object*, o->fixed(fdt));
	/*LOOPF_O(buildings, Building*, o->fixed(fdt));
	LOOPF_O(convoyers, Convoyer*, o->fixed(fdt));
	LOOPF_O(details, Object*, o->fixed(fdt));*/
}

void World::update(double dt)
{
	LOOPB_O(previews, Object*, o->update(dt));
	LOOPF_O(gameobjects, Object*, o->update(dt));
	/*LOOPF_O(buildings, Building*, o->update(dt));
	LOOPF_O(convoyers, Convoyer*, o->update(dt));
	LOOPF_O(details, Object*, o->update(dt));*/
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
	//LOOPF_O(gameobjects, Object*, win.draw(*o, states));
	LOOPF_O(buildings, Building*, win.draw(*o, states));
	LOOPF_O(convoyers, Convoyer*, win.draw(*o, states));
	LOOPF_O(previews, Object*, win.draw(*o, states));
	LOOPF_O(details, Object*, win.draw(*o, states));
}

void World::imgui()
{
	using namespace ImGui;
	
	/*if (TreeNodeEx("Gameobjects", 0)) {
		Indent(5.0f);
		LOOPF_PTR(gameobjects, Object* e);
		std::string txt = ("Object " + std::to_string(i));
		if (TreeNodeEx(txt.c_str())) {
			e->imgui();
			TreePop();
		}
		LOOP_END;
		TreePop();
	}*/
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void World::initPlayer()
{
	// Create player with a rigidbody for movement
	Object* player = new Object();
	player->rigidbody = new Rigidbody(player, { 0.0f, 0.0f });
	player->rigidbody->usePhysics = false;
	player->rigidbody->speed = C::P_SPEED;
	player->rigidbody->frx = 0.75f;
	player->rigidbody->fry = 0.75f;
	
	// Set Player position
	player->setPosition({
		C::C_CENTER_X / C::GRID_SIZE,
		C::C_CENTER_Y / C::GRID_SIZE
	});

	// Register Player Controller
	PlayerController* pc = new PlayerController(player);
	player->addComponent(pc);

	// Register player to gameobjects
	gameobjects->push_back(player);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void World::removeObject(std::vector<Object*>* quick, Object* object)
{
	if (quick != nullptr) { REMOVE_ITEM(Object*, quick, object); }
	toDelete.emplace(object);
}

void World::removePreview(Object* object)
{
	REMOVE_ITEM(Object*, previews, object);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


Object* World::getPlayer()
{
	if (gameobjects->size()) return gameobjects->operator[](0);
	return nullptr;
}

Object* World::getClosest(std::vector<Object*>* vector, sf::Vector2i gridPos)
{
	Object* target = nullptr;
	float distance = INFINITY;

	for (Object* o : *vector) {
		sf::Vector2f opos = o->getPosition();
		sf::Vector2i oposi = sf::Vector2i((int)opos.x, (int)opos.y);
		float dist = Utils::toLength(oposi - gridPos);
		if (dist < distance) {
			distance = dist;
			target = o;
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


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


Object* World::getPreview(int gridx, int gridy) const
{
	for (Object* preview : *previews) {
		if (preview->isCollision(gridx, gridy))
			return preview;
	}
	return nullptr;
}

Building* World::getBuilding(int gridx, int gridy) const
{
	for (Building* building : *buildings) {
		if (building->isCollision(gridx, gridy))
			return building;
	}
	return nullptr;
}

Convoyer* World::getConvoyer(int gridx, int gridy) const
{
	for (Convoyer* convoyer : *convoyers) {
		if (convoyer->isCollision(gridx, gridy))
			return convoyer;
	}
	return nullptr;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


InOutConvoy* World::getBuildingInput(sf::Vector2i gridPos, InOutConvoy* inOutConvoy) const
{
	// Check settings are valids (inverse mode than wanted one)
	if (inOutConvoy->mode != InOutConvoy::Mode::Out) return nullptr;

	// Check all building for an input corresponding
	InOutConvoy* convoy;
	for (Building* building : *buildings) {
		convoy = building->getInput(gridPos, inOutConvoy);
		if (convoy != nullptr) return convoy;
	}

	// No input founded
	return nullptr;
}

InOutConvoy* World::getBuildingOutput(sf::Vector2i gridPos, InOutConvoy* inOutConvoy) const
{
	// Check settings are valids (inverse mode than wanted one)
	if (inOutConvoy->mode != InOutConvoy::Mode::In) return nullptr;

	// Check all building for an output corresponding
	InOutConvoy* convoy;
	for (Building* building : *buildings) {
		convoy = building->getOutput(gridPos, inOutConvoy);
		if (convoy != nullptr) return convoy;
	}

	// No output founded
	return nullptr;
}