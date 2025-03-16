#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

// Tilemap from https://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array.php

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};