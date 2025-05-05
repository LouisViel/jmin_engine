#pragma once

#include <vector>
#include <set>
#include <unordered_set>
#include "app/M.hpp"

#include "game/object/Building.hpp"
#include "game/object/convoyer/Convoyer.hpp"

class Object;
namespace sf {
	class RenderWindow;
	class RenderTarget;
}


class World
{
private:
	// Loop Forward on gameobjects
	#define LOOPF_O(vector, type, action) \
		LOOPF_PTR(vector, type o) \
		action; \
		LOOP_END

	// Loop Backward on gameobjects
	#define LOOPB_O(vector, type, action) \
		LOOPB_PTR(vector, type o) \
		action; \
		LOOP_END

	// Object delete set (for nice cleaning)
	std::unordered_set<Object*> toDelete;

public:
	// Gameobjects container (all objects in the game)
	std::vector<Object*>* previews = nullptr;
	std::vector<Object*>* gameobjects = nullptr;

	std::vector<Building*>* buildings = nullptr;
	std::vector<Convoyer*>* convoyers = nullptr;
	// Here insert Player draw
	std::vector<Object*>* details = nullptr;
	// Here insert "Bonus" draws (style particles)

	// Render UI Gameplay
	// Render UI Utils (ex : pause, quitter jeu, ect..)
	// Render UI Help (tooltips)
	

	World(sf::RenderWindow* win);
	~World();

	void initPlayer();

	void preupdate(double dt);
	void fixed(double fdt);
	void update(double dt);
	void processDelete();
	void draw(sf::RenderTarget& win);
	void imgui();

	template<typename t>
	void removeObject(std::vector<t*>* quick, t* object);
	void removeObject(std::vector<Object*>* quick, Object* object);
	void removePreview(Object* object);

	Object* getPlayer();
	Object* getClosest(std::vector<Object*>* vector, sf::Vector2i posPix);
	bool isValid(std::vector<Object*>* vector, Object* object);

	Object* getPreview(int gridx, int gridy) const;
	Building* getBuilding(int gridx, int gridy) const;
	Convoyer* getConvoyer(int gridx, int gridy) const;

	InOutConvoy* getBuildingInput(sf::Vector2i gridPos, InOutConvoy* inOutConvoy) const;
	InOutConvoy* getBuildingOutput(sf::Vector2i gridPos, InOutConvoy* inOutConvoy) const;
};

template<typename t>
void World::removeObject(std::vector<t*>* quick, t* object)
{
	if (quick != nullptr) { REMOVE_ITEM(t*, quick, object); }
	toDelete.emplace(static_cast<Object*>(object));
}