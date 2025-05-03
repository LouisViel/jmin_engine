#include <imgui.h>
#include "Game.hpp"

#include "engine/Utils.hpp"
#include "engine/utils/InputHandler.hpp"
#include "app/M.hpp"
#include "app/C.hpp"

#include "game/core/object/Object.hpp"
#include "game/core/object/Collider.hpp"
#include "game/core/utils/Camera.hpp"
#include "game/core/Environment.hpp"
#include "game/core/World.hpp"

#include "game/core/utils/NodeType.hpp"

Game* Game::singleton = nullptr;
double Game::g_tickTimer = 0.0;
double Game::g_time = 0.0;

Game::Game(sf::RenderWindow* win)
{
	singleton = this;
	this->win = win;

	// Create Managers
	environment = new Environment(win);
	world = new World(win);

	// Create Camera
	camera = new Camera(world, { C::C_CENTER_X, C::C_CENTER_Y }, { C::C_SIZE_X, C::C_SIZE_Y });
}

Game::~Game()
{
	singleton = nullptr;
	delete environment;
	delete world;
	delete camera;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Game::preupdate(double dt)
{
	g_time += dt;
	g_tickTimer = dt;

	//mapEditor->update(dt);
	//double adt = mapEditor->active ? 0.0 : dt;

	world->preupdate(dt);
	if (InputHandler::getDebug()) {
		camera->addShake(0.5f, 1.0f);
	}
}

void Game::fixed(double fdt)
{
	world->fixed(fdt);
}

void Game::update(double dt)
{
	environment->update(dt);
	world->update(dt);
	camera->update(dt);
	world->processDelete();
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Game::draw(sf::RenderWindow& win)
{
	// Get Settings
	sf::RenderTarget* target = &win;
	sf::View defaultView = target->getView();

	// Draw World Renderings
	environment->drawWorld(*target);

	// Enable Camera Drawing
	//if (!mapEditor->active) {
		//camera->setActive(*target);
	//}

	// Draw Camera Renderings
	environment->drawCamera(*target);
	world->draw(*target);

	// Set Back target view
	target->setView(defaultView);
}

void Game::imgui()
{
	// Show Game Controls
	using namespace ImGui;
	if (CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
		if (TreeNodeEx("Clavier-Souris")) {
			Indent(1.0f);
			BulletText("Left : [Q] OU [Left arrow]");
			BulletText("Right : [D] OU [Right arrow]");
			BulletText("Up : [Z] OU [Space] OU [Up arrow]");
			BulletText("Fire Weapon : [F] OU [Left click]");
			BulletText("Switch Weapon : [E] OU [Right click]");
			BulletText("Debug Key : [P] OU [Numpad *]");
			TreePop();
		}

		if (TreeNodeEx("Manette")) {
			Indent(1.0f);
			BulletText("Left : [Left joystick] OU [Left Pad]");
			BulletText("Right : [Left joystick] OU [Left Pad]");
			BulletText("Up : [Bottom Button]");
			BulletText("Fire Weapon : [Right Button] OU [Right Trigger]");
			BulletText("Switch Weapon : [Left Button] OU [Left Trigger]");
			BulletText("Debug Key : [Menu Left]");
			TreePop();
		}
	}

	// Propagate Imgui
	environment->imgui();
	world->imgui();
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Game::processEvents(sf::Event ev)
{
	// Process window beeing closed
	if (ev.type == sf::Event::Closed) {
		win->close();
		closing = true;
		return;
	}
	
	// Process Key being released
	if (ev.type == sf::Event::KeyReleased) {

		// Key [K] for walls reset debug
		if (ev.key.code == sf::Keyboard::K) {
			//environment->debug();
			return;
		}
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


// Full check for Occupied Space
bool Game::isOccupied(Object* object) const
{
	std::vector<sf::Vector2i> collisions = std::move(object->getCollisions());
	for (sf::Vector2i& collision : collisions) {
		if (this->isOccupied(collision.x, collision.y)) return true;
	}
	return false;
}

// Full check for Occupied Space
bool Game::isOccupied(int gridx, int gridy) const
{
	return world->getPreview(gridx, gridy) != nullptr ||
		world->getBuilding(gridx, gridy) != nullptr ||
		world->getConvoyer(gridx, gridy) != nullptr;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool Game::isBuildable(Object* object) const
{
	std::vector<sf::Vector2i> collisions = std::move(object->getCollisions());
	for (sf::Vector2i& collision : collisions) {
		if (!this->isBuildable(NodeType::None, collision.x, collision.y)) return false;
	}
	return true;
}

bool Game::isBuildable(int gridx, int gridy) const
{
	return this->isBuildable(NodeType::None, gridx, gridy);
}

bool Game::isBuildable(NodeType nodeType, Object* object) const
{
	std::vector<sf::Vector2i> collisions = std::move(object->getCollisions());
	for (sf::Vector2i& collision : collisions) {
		if (!this->isBuildable(nodeType, collision.x, collision.y)) return false;
	}
	return true;
}

bool Game::isBuildable(NodeType nodeType, int gridx, int gridy) const
{
	NodeType type = NodeTypeHelper::All - nodeType + NodeTypeHelper::NonBuildable;
	if (environment->isNode(type, gridx, gridy)) return false;
	return !this->isOccupied(gridx, gridy);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


int blendModeIndex(sf::BlendMode bm) {
	if (bm == sf::BlendAlpha) return 0;
	if (bm == sf::BlendAdd) return 1;
	if (bm == sf::BlendNone) return 2;
	if (bm == sf::BlendMultiply) return 3;
	return 4;
};