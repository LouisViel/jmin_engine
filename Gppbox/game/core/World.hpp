#pragma once

#include <vector>
#include <set>
#include <unordered_set>
#include "engine/core/ParticleMan.hpp"
#include "app/M.hpp"

#include "game/object/Building.hpp"
#include "game/object/Convoyer.hpp"

class Object;
namespace sf {
	class RenderWindow;
	class RenderTarget;
}

class World
{
private:
	// Loop Forward on gameobjects
	#define LOOPF_E(action) \
		LOOPF_PTR(gameobjects, Object* e) \
		action; \
		LOOP_END

	// Loop Backward on gameobjects
	#define LOOPB_E(action) \
		LOOPB_PTR(gameobjects, Object* e) \
		action; \
		LOOP_END

	// Object delete set (for nice cleaning)
	std::unordered_set<Object*> toDelete;

public:
	std::vector<Building*>* buildings = nullptr;
	std::vector<Convoyer*>* convoyers = nullptr;
	// Here insert Player draw
	std::vector<Object*>* details = nullptr;
	// Here insert "Bonus" draws (style particles)

	// Render UI Gameplay
	// Render UI Utils (ex : pause, quitter jeu, ect..)
	// Render UI Help (tooltips)

	std::vector<Object*>* gameobjects = nullptr;
	

	World(sf::RenderWindow* win);
	~World();

	void initMainChar();
	void initPetDrone();
	Object* initEnnemy(float x, float y);
	Object* initEnnemyCore(float x, float y);

	void preupdate(double dt);
	void fixed(double fdt);
	void update(double dt);
	void processDelete();
	void draw(sf::RenderTarget& win);
	void imgui();

	void removeEnnemy(Object* ennemy);
	void removeObject(std::vector<Object*>* quick, Object* e);

	Object* getPlayer();
	Object* getEnnemy(int gridx, int gridy);
	std::set<Object*> getEnnemies(int gridx, int gridy);
	Object* getClosest(std::vector<Object*>* vector, sf::Vector2i posPix);
	bool isValid(std::vector<Object*>* vector, Object* object);
};