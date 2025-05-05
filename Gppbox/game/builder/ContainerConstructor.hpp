#pragma once
#include "game/core/builder/BuildConstructor.hpp"

class ContainerConstructor : public BuildConstructor
{
protected:
	CollisionTester* coltest = nullptr;
	sf::Vector2i anchor = sf::Vector2i(0, 0);

public:
	ContainerConstructor(sf::Vector2i anchor, sf::Vector2i size);
	virtual ~ContainerConstructor();

	bool canBuild(Game* game) override;
	Object* tryBuild() override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
