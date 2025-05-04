#include "DrillConstructor.hpp"
#include "game/core/Game.hpp"
#include "game/core/Environment.hpp"
#include "game/core/object/Collider.hpp"


DrillConstructor::DrillConstructor(sf::Vector2i anchor, sf::Vector2i size)
	: DrillConstructor(anchor, size, NodeType::None) { }

DrillConstructor::DrillConstructor(sf::Vector2i anchor, sf::Vector2i size, NodeType type)
	: anchor(anchor), type(type)
{
	this->buildType = BuildType::Building;
	coltest = new CollisionTester(size.x, size.y);
}

DrillConstructor::~DrillConstructor()
{
	delete coltest;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool DrillConstructor::canBuild(Game* game)
{
	// Process utils variables
	sf::Vector2f position = getPosition();
	sf::Vector2i pos = sf::Vector2i((int)position.x, (int)position.y);

	// Check if wanted NodeType is valid & if is buildable
	if (!game->environment->isNode(type, pos.x, pos.y)) return false;
	coltest->collider->sync(pos + anchor);
	return game->isBuildable(type, coltest);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


Object* DrillConstructor::tryBuild()
{
	throw std::exception("trybuild not implemented by default drill constructor");
	return nullptr;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void DrillConstructor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape spr = sf::RectangleShape({ 0.95f, 0.95f });
	spr.setFillColor(isDrawValid ? sf::Color::Green : sf::Color::Red);
	spr.setOutlineColor(isDrawValid ? sf::Color::Blue : sf::Color::Yellow);
	spr.setOutlineThickness(0.05f);

	sf::Vector2f position = getPosition();
	sf::Vector2i pos = sf::Vector2i((int)position.x, (int)position.y) + anchor;
	std::vector<sf::Vector2i> collisions = std::move(coltest->getCollisions());

	BuildConstructor::applyTransform(states);
	for (sf::Vector2i& col : collisions) {
		spr.setPosition((float)(pos.x - col.x), (float)(pos.y - col.y));
		if (col == pos) {
			spr.setFillColor(sf::Color::Cyan);
			target.draw(spr, states);
			spr.setFillColor(isDrawValid ? sf::Color::Green : sf::Color::Red);
		} else target.draw(spr, states);
	}
}
