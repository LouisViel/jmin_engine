#pragma once

#include <vector>
#include "engine/core/HotReloadShader.hpp"
#include "engine/utils/TileMap.hpp"

#include <tmxlite/Map.hpp>
#include "app/tmx-OrthogonalLayer.hpp"
#include "game/core/utils/NodeType.hpp"


class Environment
{
private:
	sf::RenderWindow* win;

	/*HotReloadShader* bgShader = nullptr;
	sf::Texture	bgTexture;
	sf::RectangleShape bgHandle;*/

	const bool useTmx = true;
	TileMap* environment = nullptr;
	tmx::Map* tmxMap = nullptr;
	MapLayer* tmxZero = nullptr;
	MapLayer* tmxOne = nullptr;

	std::map<uint32_t, NodeType> nodeCache;

public:
	std::vector<sf::Vector2i> walls;
	std::vector<sf::Vector2i> nodeWood;
	std::vector<sf::Vector2i> nodeStone;
	std::vector<sf::Vector2i> nodeCoal;
	std::vector<sf::Vector2i> nodeIron;

	~Environment();
	Environment(sf::RenderWindow* win);
	void initBackground();
	void initEnvironment();
	void initTmxEnvironment();

	bool isNode(NodeType nodeType, int x, int y);

	void update(double dt);
	void drawWorld(sf::RenderTarget& win);
	void drawCamera(sf::RenderTarget& win);
	void imgui();

private:
	void initTmxEnvironmentInternal(MapLayer* layer);
	NodeType getNodeType(MapLayer* layer, int x, int y);
	NodeType getNodeType(std::string tileType);
	bool isNode(std::vector<sf::Vector2i>& nodes, int x, int y);
};
