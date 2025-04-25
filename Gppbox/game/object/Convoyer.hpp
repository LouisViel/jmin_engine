#pragma once

#include "game/core/object/Object.hpp"
#include "engine/utils/TileMap.hpp"

class Convoyer : public Object
{
private:
	TileMap* tilemap = nullptr;

public:
	Convoyer();
	~Convoyer();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};