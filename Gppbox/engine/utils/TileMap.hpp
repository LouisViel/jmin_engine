#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

// Tilemap from https://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array.php

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	unsigned int width = 0;
	unsigned int height = 0;

	sf::Vector2u tileSize;
	sf::Vector2u spriteSize;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	
	bool sizeValid = false;
	bool isInit = false;

public:
	bool load(const std::string& tileset);
	void init(sf::Vector2u tileSize, sf::Vector2u spriteSize, unsigned int width, unsigned int height);
	void init(sf::Vector2u tileSize, sf::Vector2u spriteSize, unsigned int width, unsigned int height, const int* tiles);
	void init(sf::Vector2u tileSize, sf::Vector2u spriteSize, unsigned int linearSize);
	void init(sf::Vector2u tileSize, sf::Vector2u spriteSize, unsigned int linearSize, const int* tiles);

	void resize(unsigned int resizeWidth, unsigned int resizeHeight, bool keepLayout);
	void resize(unsigned int resizeWidth, unsigned int resizeHeight);
	void resize(unsigned int resizeLinearSize);

	void setPos(unsigned int idx, unsigned int idy, int posx, int posy);
	void setPos(size_t index, int x, int y);

	void setTile(unsigned int x, unsigned int y, int tileNumber);
	void setTile(size_t index, int tileNumber);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPosInternal(size_t index, int x, int y);
	void setTileInternal(size_t index, int tileNumber);
};