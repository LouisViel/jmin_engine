#include "imgui.h"
#include "Builder.hpp"

#include "engine/utils/InputHandler.hpp"
#include "engine/utils/ScaleHelper.hpp"
#include "app/C.hpp"

#include "game/core/Environment.hpp"
#include "game/core/World.hpp"
#include "game/core/Game.hpp"
#include "game/core/utils/Camera.hpp"

#include "game/builder/convoyers/ConvoyerSlowConstructor.hpp"
#include "game/builder/convoyers/ConvoyerMeanConstructor.hpp"
#include "game/builder/convoyers/ConvoyerFastConstructor.hpp"

#include "game/builder/drills/DrillWoodConstructor.hpp"
#include "game/builder/crafters/CrafterPlanksConstructor.hpp"
#include "game/builder/containers/ContainerWoodConstructor.hpp"
#include "game/builder/containers/ContainerPlanksConstructor.hpp"



Builder::Builder(sf::RenderWindow* win, Environment* environment, World* world)
	: win(win), environment(environment), world(world) { }

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
	active = constructor != nullptr;
	if (!active) return;
	valid = InputHandler::hasFocus();
	valid &= InputHandler::canUseMouse();
	if (!valid) return;
	Game* g = Game::singleton;

	// Get & Check if Mouse pos is in window 
	sf::Vector2f pos = win->mapPixelToCoords(sf::Mouse::getPosition(*win), *g->getView());
	if (pos.x < 0.0f || pos.x > C::RES_X || pos.y < 0.0f || pos.y > C::RES_Y) {
		valid = false;
		return;
	}

	// Get, Process, & Normalize Inputs
	mousePos = sf::Vector2i(int(pos.x / C::GRID_SIZE), int(pos.y / C::GRID_SIZE));
	leftButton = InputHandler::getFrameMouseLeft();
	rightButton = InputHandler::getFrameMouseRight();
	constructor->handleInputs();

	// register position to constructor for rendering & later + Check if target is occupied
	constructor->setTargetPosition(mousePos);
	#pragma warning(suppress:6011)
	occupied = !constructor->canBuild(g);

	// Destroy Object if asked to + occupied
	if (occupied && rightButton) {

		// Remove buildings & Convoyers at this position
		World* world = g->world;
		Building* building = world->getBuilding(mousePos.x, mousePos.y);
		Convoyer* convoyer = world->getConvoyer(mousePos.x, mousePos.y);
		if (building != nullptr) world->removeObject(world->buildings, building);
		if (convoyer != nullptr) world->removeObject(world->convoyers, convoyer);
		//occupied = !constructor->canBuild(g);
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
	// Dummy(ImVec2(0.0f, 6.0f));
	// ImGui::Text("Edit Mode Settings");
	// BulletText("Left click to place");

	using namespace ImGui;
	if (CollapsingHeader("Build", ImGuiTreeNodeFlags_DefaultOpen)) {
		if (TreeNodeEx("Utils", ImGuiTreeNodeFlags_DefaultOpen)) {
			Indent(1.0f);
			Text("Stop Build mode + Erase preview");

			if (Button("Nothing")) switchConstructor(nullptr);

			TreePop();
		}

		Spacing();
		if (TreeNodeEx("Convoyers", ImGuiTreeNodeFlags_DefaultOpen)) {
			Indent(1.0f);
			Text("Switch Build Mode to end/connect your convoyer");

			if (Button("Slow Convoy")) switchConstructor((new ConvoyerSlowConstructor())->constructor());
			SameLine(0.0f, 10.0f);
			if (Button("Mean Convoy")) switchConstructor((new ConvoyerMeanConstructor())->constructor());
			SameLine(0.0f, 10.0f);
			if (Button("Fast Convoy")) switchConstructor((new ConvoyerFastConstructor())->constructor());

			TreePop();
		}

		Spacing();
		if (TreeNodeEx("Drills", ImGuiTreeNodeFlags_DefaultOpen)) {
			Indent(1.0f);
			Text("Build you drills on Ressources Nodes");

			if (Button("Wood Drill")) switchConstructor((new DrillWoodConstructor(1.0f))->constructor());
			SameLine(0.0f, 10.0f);
			if (Button("Forest Cutter")) switchConstructor((new DrillWoodConstructor(2.0f))->constructor());
			SameLine(0.0f, 10.0f);
			if (Button("Planet Killer")) switchConstructor((new DrillWoodConstructor(5.0f))->constructor());

			TreePop();
		}

		/*Spacing();
		if (TreeNodeEx("Melters", ImGuiTreeNodeFlags_DefaultOpen)) {
			Indent(1.0f);
			TreePop();
		}*/

		Spacing();
		if (TreeNodeEx("Crafters", ImGuiTreeNodeFlags_DefaultOpen)) {
			Indent(1.0f);
			Text("Advanced Ressources Crafters");

			if (Button("Planks")) switchConstructor((new CrafterPlanksConstructor(1.0f))->constructor());
			SameLine(0.0f, 10.0f);
			if (Button("Planks Ultra")) switchConstructor((new CrafterPlanksConstructor(2.0f))->constructor());
			SameLine(0.0f, 10.0f);
			if (Button("GTA VI Maker")) switchConstructor((new CrafterPlanksConstructor(5.0f))->constructor());

			TreePop();
		}

		Spacing();
		if (TreeNodeEx("Containers", ImGuiTreeNodeFlags_DefaultOpen)) {
			Indent(1.0f);
			Text("Resources containers (scores visible in Imgui)");

			if (Button("Wood Container")) switchConstructor((new ContainerWoodConstructor())->constructor());
			SameLine(0.0f, 10.0f);
			if (Button("Planks Container")) switchConstructor((new ContainerPlanksConstructor())->constructor());
			
			TreePop();
		}
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