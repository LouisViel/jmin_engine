#include "ContainerConstructor.hpp"
#include "game/core/Game.hpp"
#include "game/core/Environment.hpp"
#include "game/core/object/Collider.hpp"


ContainerConstructor::ContainerConstructor(sf::Vector2i anchor, sf::Vector2i size) : anchor(anchor)
{
	this->buildType = BuildType::Building;
	coltest = new CollisionTester(size.x, size.y);
}

ContainerConstructor::~ContainerConstructor()
{
	delete coltest;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool ContainerConstructor::canBuild(Game* game)
{
	// Process utils variables
	sf::Vector2f position = getPosition();
	sf::Vector2i pos = sf::Vector2i((int)position.x, (int)position.y);

	// Check if is buildable
	coltest->collider->sync(pos + anchor);
	return game->isBuildable(NodeTypeHelper::Buildable, coltest);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


Object* ContainerConstructor::tryBuild()
{
	throw std::exception("trybuild not implemented by default container constructor");
	return nullptr;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void ContainerConstructor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape spr = sf::RectangleShape({ 0.95f, 0.95f });
	spr.setFillColor(isDrawValid ? sf::Color::Green : sf::Color::Red);
	spr.setOutlineColor(isDrawValid ? sf::Color::Blue : sf::Color::Yellow);
	spr.setOutlineThickness(0.05f);

	sf::Vector2f position = getPosition();
	sf::Vector2i pos = sf::Vector2i((int)position.x, (int)position.y);
	std::vector<sf::Vector2i> collisions = std::move(coltest->getCollisions());

	BuildConstructor::applyTransform(states);
	for (sf::Vector2i& col : collisions) {
		spr.setPosition((float)(pos.x - col.x), (float)(pos.y - col.y));
		target.draw(spr, states);
	}
}
