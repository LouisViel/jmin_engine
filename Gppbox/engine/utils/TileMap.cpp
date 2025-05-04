#include "TileMap.hpp"


bool TileMap::load(const std::string& tileset)
{
    return m_tileset.loadFromFile(tileset);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void TileMap::init(sf::Vector2u tileSize, sf::Vector2u spriteSize, unsigned int width, unsigned int height)
{
    // Save settings
    this->isInit = true;
    this->tileSize = tileSize;
    this->spriteSize = spriteSize;
    this->width = width;
    this->height = height;

    // resize the vertex array to fit the level size
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    this->resize(width, height, false);
}

void TileMap::init(sf::Vector2u tileSize, sf::Vector2u spriteSize, unsigned int width, unsigned int height, const int* tiles)
{
    // Basic settings loading
    this->init(tileSize, spriteSize, width, height);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            size_t index = static_cast<size_t>((i + j * width) * 4);
            this->setPosInternal(index, i, j);
            this->setTileInternal(index, tiles[i + j * width]);
        }
    }
}

void TileMap::init(sf::Vector2u tileSize, sf::Vector2u spriteSize, unsigned int linearSize)
{
    this->init(tileSize, spriteSize, linearSize, 1u);
}

void TileMap::init(sf::Vector2u tileSize, sf::Vector2u spriteSize, unsigned int linearSize, const int* tiles)
{
    this->init(tileSize, spriteSize, linearSize, 1u, tiles);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void TileMap::resize(unsigned int resizeWidth, unsigned int resizeHeight, bool keepLayout)
{
    // Resize container
    unsigned int resSize = resizeWidth * resizeHeight;
    if (resSize > 0) {
        m_vertices.resize(static_cast<size_t>(resizeWidth * resizeHeight * 4));
        sizeValid = true;
    } else {
        keepLayout = false;
        m_vertices.clear();
        sizeValid = false;
    }

    // Change tiles indexes to keep them in place
    if (keepLayout) {
        unsigned int targetWidth = std::min(width, resizeWidth);
        unsigned int targetHeight = std::min(height, resizeHeight);
        for (unsigned int i = targetWidth; i > 0; --i) {
            for (unsigned int j = targetHeight; j > 0; --j) {
                unsigned int ui = i - 1, uj = j - 1;
                size_t srcIndex = static_cast<size_t>((ui + uj * width) * 4);
                size_t targIndex = static_cast<size_t>((ui + uj * resizeWidth) * 4);
                m_vertices[targIndex] = sf::Vertex(m_vertices[srcIndex]);
                m_vertices[targIndex + 1] = sf::Vertex(m_vertices[srcIndex + 1]);
                m_vertices[targIndex + 2] = sf::Vertex(m_vertices[srcIndex + 2]);
                m_vertices[targIndex + 3] = sf::Vertex(m_vertices[srcIndex + 3]);
            }
        }
    }

    // Save settings
    this->width = resizeWidth;
    this->height = resizeHeight;
}

void TileMap::resize(unsigned int resizeWidth, unsigned int resizeHeight)
{
    this->resize(resizeWidth, resizeHeight, true);
}

void TileMap::resize(unsigned int resizeLinearSize)
{
    this->resize(resizeLinearSize, 1u, false);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void TileMap::setPos(unsigned int idx, unsigned int idy, int posx, int posy)
{
    this->setPosInternal(static_cast<size_t>((idx + idy * width) * 4), posx, posy);
}

void TileMap::setPos(size_t index, int x, int y)
{
    this->setPosInternal(static_cast<size_t>(index * 4), x, y);
}

void TileMap::setPosInternal(size_t index, int x, int y)
{
    // Ensure operation valid
    if (!sizeValid) return;

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
    this->setTileInternal(static_cast<size_t>((x + y * width) * 4), tileNumber);
}

void TileMap::setTile(size_t index, int tileNumber)
{
    this->setTileInternal(static_cast<size_t>(index * 4), tileNumber);
}

void TileMap::setTileInternal(size_t index, int tileNumber)
{
    // Ensure operation valid
    if (!sizeValid) return;

    // find position in the tileset texture
    int tu = tileNumber % (m_tileset.getSize().x / spriteSize.x);
    int tv = tileNumber / (m_tileset.getSize().x / spriteSize.x);

    // define 4 texture corner coordinates
    sf::Vertex* quad = &m_vertices[index];
    quad[0].texCoords = sf::Vector2f((float)tu * spriteSize.x, (float)tv * spriteSize.y);
    quad[1].texCoords = sf::Vector2f((float)(tu + 1) * spriteSize.x, (float)tv * spriteSize.y);
    quad[2].texCoords = sf::Vector2f((float)(tu + 1) * spriteSize.x, (float)(tv + 1) * spriteSize.y);
    quad[3].texCoords = sf::Vector2f((float)tu * spriteSize.x, (float)(tv + 1) * spriteSize.y);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!(isInit && sizeValid)) return;
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}