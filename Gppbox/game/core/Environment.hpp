#pragma once

#include <vector>
#include "engine/core/HotReloadShader.hpp"
#include "engine/utils/TileMap.hpp"

class Environment
{
public:
	sf::RenderWindow* win;

	HotReloadShader* bgShader = nullptr;
	sf::Texture	bgTexture;
	sf::RectangleShape bgHandle;

	TileMap* environment = nullptr;
	std::vector<sf::Vector2i> collisions;

	~Environment();
	Environment(sf::RenderWindow* win);
	void initBackground();
	void initEnvironment();

	void update(double dt);
	void drawWorld(sf::RenderTarget& win);
	void drawCamera(sf::RenderTarget& win);
	void imgui();
};
