#pragma once

#include "app/sys.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class Object;
class Builder;
class Environment;
class World;
class MapEditor;
class Camera;
enum class NodeType;

class Game {
public:
	static Game* singleton;

	sf::RenderWindow* win = nullptr;
	bool closing = false;
	
	Builder* builder = nullptr;
	Environment* environment = nullptr;
	World* world = nullptr;
	Camera* camera = nullptr;

	
	~Game();
	Game(sf::RenderWindow * win);

	void preupdate(double dt);
	void fixed(double fdt);
	void update(double dt);
	void draw(sf::RenderWindow& win);
	void imgui();

	void processEvents(sf::Event ev);

	bool isOccupied(Object* object) const;
	bool isOccupied(int gridx, int gridy) const;

	bool isBuildable(Object* object) const;
	bool isBuildable(int gridx, int gridy) const;
	bool isBuildable(NodeType nodeType, Object* object) const;
	bool isBuildable(NodeType nodeType, int gridx, int gridy) const;

	sf::View* getView() const;
};