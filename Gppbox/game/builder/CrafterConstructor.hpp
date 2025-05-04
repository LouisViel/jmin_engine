#pragma once
#include "game/core/builder/BuildConstructor.hpp"

class CrafterConstructor : public BuildConstructor
{
	CollisionTester* coltest = nullptr;
	sf::Vector2i anchor = sf::Vector2i(0, 0);

public:
	CrafterConstructor(sf::Vector2i anchor, sf::Vector2i size);
	virtual ~CrafterConstructor();

	bool canBuild(Game* game) override;
	Object* tryBuild() override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
