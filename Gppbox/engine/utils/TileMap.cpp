#include "TileMap.hpp"


bool TileMap::load(const std::string& tileset)
{
    return m_tileset.loadFromFile(tileset);
}

void TileMap::init(sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    // Save settings
    this->isInit = true;
    this->tileSize = tileSize;
    this->width = width;
    this->height = height;

    // resize the vertex array to fit the level size
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(static_cast<size_t>(width * height * 4));
}

void TileMap::init(sf::Vector2u tileSize, unsigned int width, unsigned int height, const int* tiles)
{
    // Basic settings loading
    this->init(tileSize, width, height);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            size_t index = static_cast<size_t>((i + j * width) * 4);
            this->setPos(index, i, j);
            this->setTile(index, tiles[i + j * width]);
        }
    }
}

void TileMap::init(sf::Vector2u tileSize, unsigned int linearSize)
{
    this->init(tileSize, linearSize, 1u);
}

void TileMap::init(sf::Vector2u tileSize, unsigned int linearSize, const int* tiles)
{
    this->init(tileSize, linearSize, 1u, tiles);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void TileMap::setPos(unsigned int idx, unsigned int idy, int posx, int posy)
{
    this->setPos(static_cast<size_t>((idx + idy * width) * 4), posx, posy);
}

void TileMap::setPos(size_t index, int x, int y)
{
    // define 4 corners positions
    sf::Vertex* quad = &m_vertices[index];
    quad[0].position = sf::Vector2f((float)x * tileSize.x, (float)y * tileSize.y);
    quad[1].position = sf::Vector2f((float)(x + 1) * tileSize.x, (float)y * tileSize.y);
    quad[2].position = sf::Vector2f((float)(x + 1) * tileSize.x, (float)(y + 1) * tileSize.y);
    quad[3].position = sf::Vector2f((float)x * tileSize.x, (float)(y + 1) * tileSize.y);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void TileMap::setTile(unsigned int x, unsigned int y, int tileNumber)
{
    this->setTile(static_cast<size_t>((x + y * width) * 4), tileNumber);
}

void TileMap::setTile(size_t index, int tileNumber)
{
    // find position in the tileset texture
    int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
    int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

    // define 4 texture corner coordinates
    sf::Vertex* quad = &m_vertices[index];
    quad[0].texCoords = sf::Vector2f((float)tu * tileSize.x, (float)tv * tileSize.y);
    quad[1].texCoords = sf::Vector2f((float)(tu + 1) * tileSize.x, (float)tv * tileSize.y);
    quad[2].texCoords = sf::Vector2f((float)(tu + 1) * tileSize.x, (float)(tv + 1) * tileSize.y);
    quad[3].texCoords = sf::Vector2f((float)tu * tileSize.x, (float)(tv + 1) * tileSize.y);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!isInit) return;
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}