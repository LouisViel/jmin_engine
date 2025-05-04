#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "BuildConstructor.hpp"

class Game;
class Environment;
class World;

class Builder
{
protected:
	sf::RenderWindow* win;
	Environment* environment;
	World* world;

	// Process values
	BuildConstructor* constructor = nullptr;
	bool occupied = false;
	
	// Inputs
	bool leftButton = false;
	bool rightButton = false;
	sf::Vector2i mousePos;

public:
	// States
	bool active = false;
	bool valid = false;

public:
	Builder(sf::RenderWindow* win, Environment* environment, World* world);
	~Builder();

	void update(double dt);
	void draw(sf::RenderTarget& win);
	void imgui();

private:
	inline void switchConstructor(BuildConstructor* constructor);
};
