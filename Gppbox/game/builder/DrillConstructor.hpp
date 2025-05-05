#pragma once
#include "game/core/builder/BuildConstructor.hpp"
#include "game/core/utils/NodeType.hpp"

class DrillConstructor : public BuildConstructor
{
protected:
	NodeType type = NodeType::None;
	CollisionTester* coltest = nullptr;
	sf::Vector2i anchor = sf::Vector2i(0, 0);

public:
	float speed = 1.0f;

public:
	DrillConstructor(sf::Vector2i anchor, sf::Vector2i size);
	DrillConstructor(sf::Vector2i anchor, sf::Vector2i size, float speed);
	DrillConstructor(sf::Vector2i anchor, sf::Vector2i size, NodeType type);
	DrillConstructor(sf::Vector2i anchor, sf::Vector2i size, NodeType type, float speed);
	virtual ~DrillConstructor();

	bool canBuild(Game* game) override;
	Object* tryBuild() override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
