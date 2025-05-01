#pragma once
#include <vector>
#include "ConvoyerItem.hpp"
#include "game/core/object/Object.hpp"
#include "game/core/payload/InOutConvoy.hpp"
#include "game/object/convoyer/ConvoyerTile.hpp"
#include "engine/utils/TileMap.hpp"

class Convoyer : public Object
{
private:
	TileMap* tilemap = nullptr;
	std::vector<sf::Vector2i>* parts = nullptr;
	std::vector<ConvoyerItem*>* items = nullptr;
	InOutConvoyDefault* inputHandle = nullptr;
	InOutConvoyDefault* outputHandle = nullptr;

	bool multiPart = false;
	sf::Vector2i endPos;

public:
	float speed = 1.0f;

public:
	Convoyer();
	~Convoyer();
	void preupdate(double dt) override;
	void update(double dt) override;

	void build(sf::Vector2i startPos, sf::Vector2i endPos, std::vector<sf::Vector2i> tiles);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool processItem(ConvoyerItem* previous, ConvoyerItem* item, float partSize, float dt);

	inline ConvoyerTile getTile(const sf::Vector2i& origin, const sf::Vector2i& pos, const sf::Vector2i& end);
	ConvoyerTile getTile(const sf::Vector2i& origin, const sf::Vector2i& pos, const sf::Vector2i& end, int specialId);
};