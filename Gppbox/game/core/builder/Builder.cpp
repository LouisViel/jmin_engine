#include "imgui.h"
#include "Builder.hpp"
#include "engine/utils/InputHandler.hpp"
#include "engine/utils/ScaleHelper.hpp"
#include "game/core/Environment.hpp"
#include "game/core/World.hpp"
#include "game/core/Game.hpp"
#include "app/C.hpp"


Builder::Builder(sf::RenderWindow* win, sf::RenderTarget* camTarget, Environment* environment, World* world)
	: win(win), camTarget(camTarget), environment(environment), world(world) { }

Builder::~Builder()
{
	if (constructor != nullptr) {
		delete constructor;
		constructor = nullptr;
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Builder::update(double dt)
{
	// Check is active and if game focused
	if (!active) return;
	valid = InputHandler::hasFocus();
	valid &= InputHandler::canUseMouse();
	valid &= constructor != nullptr;
	if (!valid) return;

	// TODO : le système de coordinates (2 blocs de code suivants) est maybe cassé
	// Il était prévu pour un edit full screen et non vue caméra

	// Get & Check if Mouse pos is in window 
	sf::Vector2f pos = camTarget->mapPixelToCoords(sf::Mouse::getPosition(*win));
	if (pos.x < 0.0f || pos.x > C::RES_X || pos.y < 0.0f || pos.y > C::RES_Y) {
		valid = false;
		return;
	}

	// Get, Process, & Normalize Inputs
	mousePos = sf::Vector2i(int(pos.x / C::GRID_SIZE), int(pos.y / C::GRID_SIZE));
	leftButton = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	rightButton = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	constructor->handleInputs();

	// register position to constructor for rendering & later + Check if target is occupied
	Game* g = Game::singleton;
	constructor->setTargetPosition(mousePos);
	#pragma warning(suppress:6011)
	occupied = constructor->canBuild(g);

	// Destroy Object if asked to + occupied
	if (occupied && rightButton) {
		//removeAny();
		occupied = constructor->canBuild(g);
	}

	// Spawn Object if asked to + not occupied 
	if (!occupied && leftButton) {
		Object* build = constructor->tryBuild();
		if (build != nullptr) {
			g->world->gameobjects->push_back(build);
			if (constructor->isConvoyer()) g->world->convoyers->push_back(static_cast<Convoyer*>(build));
			else if (constructor->isBuilding()) g->world->buildings->push_back(static_cast<Building*>(build));
			else throw std::exception("Constructor has no identity. Please specify it !!");
			occupied = true;
		}
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Builder::draw(sf::RenderTarget& target)
{
	if (constructor == nullptr) return;
	sf::RenderStates states = sf::RenderStates::Default;
	states.transform *= ScaleHelper::apply();
	constructor->isDrawValid = !occupied;
	target.draw(*constructor, states);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Builder::imgui()
{
	// BuildConstructor for handles
	// TODO : Ici on draw les boutons de build des batiments (par categorie)
	// Quand on click dessus, on toggle (enable/disable) des
	// "ConvoyerBuilder" (plusieurs, même chose mais avec différentes speeds)
	// "BuildingBuilder" (plusieurs catégories (drill, four, constructor, ect..), avec plusieurs pour les types dedans)

	using namespace ImGui;
	if (CollapsingHeader("Build", ImGuiTreeNodeFlags_DefaultOpen)) {
		if (TreeNodeEx("Convoyers", ImGuiTreeNodeFlags_DefaultOpen)) {
			Indent(1.0f);

			TreePop();
		}

		if (TreeNodeEx("Drills", ImGuiTreeNodeFlags_DefaultOpen)) {
			Indent(1.0f);

			TreePop();
		}

		// SameLine();
		// BulletText("Left click to place");

		// Editor Toggle Button
		/*Dummy(ImVec2(0.0f, 6.0f));
		ImGui::Text("Edit Mode Settings");
		if (active && Button("Go back Playing")) active = false;
		if (!active && Button("Enter Edit Mode")) active = true;*/

		TreePop();
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


inline void Builder::switchConstructor(BuildConstructor* constructor)
{
	if (this->constructor != nullptr) delete this->constructor;
	this->constructor = constructor;
}