#pragma once
#include <vector>
#include "game/core/object/Object.hpp"
#include "game/core/payload/InOutConvoy.hpp"
#include "game/object/convoyer/ConvoyerTile.hpp"
#include "engine/utils/TileMap.hpp"
#include "ConvoyerItem.hpp"

class Convoyer : public Object
{
private:
	TileMap* tilemap = nullptr;
	std::vector<sf::Vector2i>* parts = nullptr;
	sf::Vector2i endPos = sf::Vector2i(0, 0);
	bool multiPart = false;

	std::vector<ConvoyerItem*>* items = nullptr;
	InOutConvoyDefault* inputHandle = nullptr;
	InOutConvoyDefault* outputHandle = nullptr;

public:
	float speed = 1.0f;

public:
	Convoyer();
	Convoyer(float speed);
	virtual ~Convoyer();
	size_t size();

	void preupdate(double dt) override;
	void update(double dt) override;

	// Positions are in relative space to convoyer (getPosition()) (first part should be (0, 0))
	void build(sf::Vector2i startPos, sf::Vector2i endPos, std::vector<sf::Vector2i>& tiles);
	void expand(sf::Vector2i endPos, std::vector<sf::Vector2i>& tiles);
	void remove(size_t partsCount);
	void remove(sf::Vector2i cutPos);

	// Callers for internal convertion from world to local space
	void buildWorld(sf::Vector2i startPos, sf::Vector2i endPos, std::vector<sf::Vector2i>& tiles, bool convertTiles = true);
	void expandWorld(sf::Vector2i endPos, std::vector<sf::Vector2i>& tiles, bool convertTiles = true);
	void removeWorld(sf::Vector2i cutPos);

	bool connectInput(InOutConvoy* const input);
	bool connectOutput(InOutConvoy* const output);
	void removeInput();
	void removeOutput();

	bool isCollision(int gridx, int gridy) const override;
	std::vector<sf::Vector2i> getCollisions() const override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool processItem(ConvoyerItem* previous, ConvoyerItem* item, float partSize, float dt);

	inline ConvoyerTile getTile(const sf::Vector2i& origin, const sf::Vector2i& pos, const sf::Vector2i& end);
	ConvoyerTile getTile(const sf::Vector2i& origin, const sf::Vector2i& pos, const sf::Vector2i& end, int specialId);
};