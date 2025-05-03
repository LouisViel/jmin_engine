#include <imgui.h>
#include "Environment.hpp"
#include "engine/utils/ScaleHelper.hpp"
#include "app/C.hpp"


Environment::Environment(sf::RenderWindow* win)
{
	this->win = win;
	if (useTmx) initTmxEnvironment();
	else initEnvironment();
	initBackground();
}

Environment::~Environment()
{
	delete bgShader;
	if (useTmx) {
		delete tmxZero;
		delete tmxMap;
	} else delete environment;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Environment::initBackground()
{
	bool isOk = bgTexture.loadFromFile("res/bg_city.jpg");
	if (!isOk) printf("ERR : LOAD FAILED\n");
	bgHandle = sf::RectangleShape(sf::Vector2f((float)win->getSize().x, (float)win->getSize().y));
	bgHandle.setTexture(&bgTexture);
	bgHandle.setSize(sf::Vector2f(C::RES_X, C::RES_Y));
	bgShader = new HotReloadShader("res/bg.vert", "res/bg.frag");
}

void Environment::initEnvironment()
{
	throw std::exception(); // Will not be implemented cause using tmx instead
	//environment = new TileMap();
	//environment->load();
}

void Environment::initTmxEnvironment()
{
	// Init Tmx Tilemap
	tmxMap = new tmx::Map();
	tmxMap->load(C::TMX_FILE);
	tmxZero = new MapLayer(*tmxMap, 0);
	
	// Register Node Locations
	tmx::Vector2u tileCount = tmxMap->getTileCount();
	for (int x = 0; x < (int)tileCount.x; ++x) {
		for (int y = 0; y < (int)tileCount.y; ++y) {
			NodeType nodeType = getNodeType(x, y);
#pragma warning( push )
#pragma warning( disable : 26813)
			if (nodeType == NodeType::Wall) walls.push_back(sf::Vector2i(x, y));
			else if (nodeType == NodeType::Wood) nodeWood.push_back(sf::Vector2i(x, y));
			else if (nodeType == NodeType::Stone) nodeStone.push_back(sf::Vector2i(x, y));
			else if (nodeType == NodeType::Coal) nodeCoal.push_back(sf::Vector2i(x, y));
			else if (nodeType == NodeType::Iron) nodeIron.push_back(sf::Vector2i(x, y));
#pragma warning( pop )
		}
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


NodeType Environment::getNodeType(int x, int y)
{
	// Fetch cache for better performances
	uint32_t id = tmxZero->getTile(x, y).ID;
	if (nodeCache.find(id) != nodeCache.end()) {
		return nodeCache.at(id);
	}
	
	// If no cache, process to a search and resolution
	for (tmx::Tileset tileset : tmxMap->getTilesets()) {
		if (tileset.hasTile(id)) {
			std::string tileType = tileset.getTile(id)->className;
			NodeType nodeType = getNodeType(tileType);
			if (nodeType != NodeType::None) {
				nodeCache.insert({ id, nodeType });
				return nodeType;
			}
		}
	}

	// Return None if no resolution possible
	nodeCache.insert({ id, NodeType::None });
	return NodeType::None;
}

NodeType Environment::getNodeType(std::string tileType)
{
	if (tileType == "Node-Wall") return NodeType::Wall;
	if (tileType == "Node-Wood") return NodeType::Wood;
	if (tileType == "Node-Stone") return NodeType::Stone;
	if (tileType == "Node-Coal") return NodeType::Coal;
	if (tileType == "Node-Iron") return NodeType::Iron;
	return NodeType::None;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool Environment::isNode(NodeType nodeType, int x, int y)
{
	if ((nodeType & NodeType::Wall) != NodeType::None && isNode(walls, x, y)) return true;
	if ((nodeType & NodeType::Wood) != NodeType::None && isNode(nodeWood, x, y)) return true;
	if ((nodeType & NodeType::Stone) != NodeType::None && isNode(nodeStone, x, y)) return true;
	if ((nodeType & NodeType::Coal) != NodeType::None && isNode(nodeCoal, x, y)) return true;
	if ((nodeType & NodeType::Iron) != NodeType::None && isNode(nodeIron, x, y)) return true;
	return false;
}

bool Environment::isNode(std::vector<sf::Vector2i>& nodes, int x, int y)
{
	for (sf::Vector2i& node : nodes)
		if (node.x == x && node.y == y) return true;
	return false;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Environment::update(double dt)
{
	if (bgShader) bgShader->update(dt);
	tmxZero->update(sf::seconds((float)dt));
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Environment::drawWorld(sf::RenderTarget& win)
{
	sf::RenderStates states = sf::RenderStates::Default;
	states.transform *= ScaleHelper::apply();
	return;
}

void Environment::drawCamera(sf::RenderTarget& win)
{
	// Draw Background
	sf::RenderStates states = sf::RenderStates::Default;
	sf::Shader* sh = &bgShader->sh;
	states.blendMode = sf::BlendAdd;
	states.shader = sh;
	states.texture = &bgTexture;
	sh->setUniform("texture", bgTexture);
	win.draw(bgHandle, states);

	// Draw Environment, using Tmx or Custom Tilemap
	if (useTmx) win.draw(*tmxZero, sf::RenderStates::Default);
	else win.draw(*environment, sf::RenderStates::Default);
}

void Environment::imgui()
{
	using namespace ImGui;
	//if (CollapsingHeader("World", ImGuiTreeNodeFlags_DefaultOpen)) {

	//	// Draw Debug Walls
	//	/*if (TreeNodeEx("Collisions")) {
	//		for (sf::Vector2i& w : collisions) {
	//			Value("x", w.x);
	//			Value("y", w.y);
	//		}
	//		TreePop();
	//	}*/
	//}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


// Cache Walls to Graphics
//void Environment::cacheWalls()
//{
//	wallSprites.clear();
//	for (sf::Vector2i& w : walls) {
//		sf::RectangleShape rect(sf::Vector2f(C::GRID_SIZE, C::GRID_SIZE));
//		rect.setPosition((float)w.x * C::GRID_SIZE, (float)w.y * C::GRID_SIZE);
//		//rect.setFillColor(sf::Color(0x07ff07ff));
//		rect.setTexture(&wallTexture);
//		wallSprites.push_back(rect);
//	}
//}