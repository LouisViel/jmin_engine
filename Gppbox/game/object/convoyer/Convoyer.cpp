#include "Convoyer.hpp"
#include "engine/Utils.hpp"
#include "engine/utils/TransformHelper.hpp"


Convoyer::Convoyer()
{
    // Setup Input Handle (with default settings) (Need to be updated later)
    inputHandle = new InOutConvoyDefault(InOutConvoy::Mode::In, ResourceTypeHelper::All, DirectionHelper::All);
    inputHandle->anchor = sf::Vector2i(0, 0);
    //inputHandle->payload = nullptr;
    inputHandle->managePayload = false;

    // Setup Output Handle (with default settings) (Need to be updated later)
    outputHandle = new InOutConvoyDefault(InOutConvoy::Mode::Out, ResourceTypeHelper::All, DirectionHelper::All);
    outputHandle->anchor = sf::Vector2i(0, 0);
    //outputHandle->payload = nullptr;
    outputHandle->managePayload = false;

    // Setup convoyer parts & items containers
    parts = new std::vector<sf::Vector2i>();
    items = new std::vector<ConvoyerItem*>();

    // Setup rendering
    tilemap = new TileMap();
    tilemap->load(C::CONVOYER_TILESET);
}

Convoyer::~Convoyer()
{
    // Delete all items remaining on convoyer
    LOOPF_PTR(items, ConvoyerItem* item);
    PayloadPool::free(item->payload);
    ConvoyerItemPool::free(item);
    LOOP_END;
    delete items;

    // Delete other handles
    delete inputHandle;
    delete outputHandle;
    delete tilemap;
    delete parts;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void Convoyer::build(sf::Vector2i startPos, sf::Vector2i endPos, std::vector<sf::Vector2i> tiles)
{
    // Prevent weird invocation of build method
    if (tiles.size() <= 0) throw std::exception("Cannot build a convoyer without tiles");

    // Initialize tilemap with specified settings
    const unsigned int gridSize = (unsigned int)C::GRID_SIZE;
    sf::Vector2u tileSize = sf::Vector2u(gridSize, gridSize);
    tilemap->init(tileSize, (unsigned int)tiles.size());
    tilemap->setPosition((float)startPos.x, (float)startPos.y);
    
    // Register part settings
    this->multiPart = tiles.size() > 1;
    this->endPos = endPos;

    // Set Start part (special treatment)
    const sf::Vector2i noTile = sf::Vector2i(0, 0);
    sf::Vector2i startTile = tiles[0];
    sf::Vector2i targetTile = multiPart ? tiles[1] : endPos;
    tilemap->setPos(0, startTile.x, startTile.y);
    tilemap->setTile(0, &getTile(noTile, startTile, targetTile, 1));

    // Set intermediate parts (basic treatments)
    for (int i = 1; i < (int)tiles.size() - 1; ++i) {
        size_t id = static_cast<size_t>(i);
        sf::Vector2i& previousTile = tiles[id - 1];
        sf::Vector2i& tile = tiles[id];
        sf::Vector2i& nextTile = tiles[id + 1];
        tilemap->setPos(id, tile.x, tile.x);
        tilemap->setTile(id, &getTile(previousTile, tile, nextTile));
    }

    // Set End part (special treatment)
    if (multiPart) {
        size_t idEnd = tiles.size() - 1;
        sf::Vector2i prevTile = tiles.at(idEnd - 1);
        sf::Vector2i endTile = tiles.at(idEnd);
        tilemap->setPos(idEnd, endTile.x, endTile.y);
        tilemap->setTile(idEnd, &getTile(prevTile, endTile, endPos, 2));
    }

    // Register parts of convoyer
    parts->clear();
    parts->insert(parts->begin(), tiles.begin(), tiles.end());
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Convoyer::preupdate(double dt)
{
    // Cannot update without convoyer parts
    if (parts->size() <= 0) return;

    // Setup utils variables
    float fdt = (float)dt;
    float partSize = (float)parts->size() - 0.001f;
    ConvoyerItem* previous = nullptr;

    // Update already on convoyer items
    LOOPF_PTR(items, ConvoyerItem* item);
    if (processItem(previous, item, partSize, fdt)) {
        items->erase(items->begin() + i--);
        ConvoyerItemPool::free(item);
    } else previous = item;
    LOOP_END;

    // Add & Update convoyer items from input buffer
    #pragma warning(suppress:6011)
    while (inputHandle->payload->valid() && (previous == nullptr || previous->progression - 1.0f >= 0.0f)) {
        ConvoyerItem* item = ConvoyerItemPool::get(inputHandle->payload->pop());
        if (!processItem(previous, item, partSize, fdt)) {
            items->emplace_back(item);
            previous = item;
        } else ConvoyerItemPool::free(item);
    }
}

bool Convoyer::processItem(ConvoyerItem* previous, ConvoyerItem* item, float partSize, float dt)
{
    // Update progression + Push to output buffer if reached & possible
    item->progression += dt * speed;
    if (previous != nullptr) item->progression = std::min(item->progression, previous->progression - 1.0f);
    if (item->progression >= partSize) {
        item->progression = partSize;
        return outputHandle->payload->push(item->payload);
    }
    return false;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Convoyer::update(double dt)
{
    // Cannot render without convoyer parts
    if (parts->size() <= 0) return;

    // Update items render positions
    LOOPF_PTR(items, ConvoyerItem* item);
    int partId = static_cast<int>(item->progression);
    sf::Vector2i& start = parts->operator[](partId), end = parts->operator[](partId + 1);
    item->pos = Utils::lerp(start, end, item->progression - partId);
    LOOP_END;
}

void Convoyer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // call Object inheritance draw
    Object::drawInternal(target, states);
    Object::applyTransform(states);

    // Render convoyer
    target.draw(*tilemap, states);
    states.transform *= tilemap->getTransform();

    // Render convoyer items
    sf::Transform transform = states.transform;
    TransformHelper helper = TransformHelper();
    LOOPF_PTR(items, ConvoyerItem* item);
    helper.setPosition(item->pos);
    states.transform = transform * helper.getTransform();
    target.draw(*item->payload->render, states);
    LOOP_END;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


inline ConvoyerTile Convoyer::getTile(const sf::Vector2i& origin, const sf::Vector2i& pos, const sf::Vector2i& end)
{
    return getTile(origin, pos, end, 0);
}

ConvoyerTile Convoyer::getTile(const sf::Vector2i& origin, const sf::Vector2i& pos, const sf::Vector2i& end, int specialId)
{
    // Calculate diff between end & pos & start
    sf::Vector2i startDir = pos - origin;
    sf::Vector2i endDir = end - pos;

    // Special - Start
    if (specialId == 1) {
        if (startDir.x > 0) {
            if (endDir.x > 0) return ConvoyerTile::RightStart;
        } else if (startDir.x < 0) {
            if (endDir.x < 0) return ConvoyerTile::LeftStart;
        } else if (startDir.y > 0) {
            if (endDir.y > 0) return ConvoyerTile::DownStart;
        } else if (startDir.y < 0) {
            if (endDir.y < 0) return ConvoyerTile::TopStart;
        }
    }

    // Special - End
    if (specialId == 2) {
        if (startDir.x > 0) {
            if (endDir.x > 0) return ConvoyerTile::RightEnd;
        } else if (startDir.x < 0) {
            if (endDir.x < 0) return ConvoyerTile::LeftEnd;
        } else if (startDir.y > 0) {
            if (endDir.y > 0) return ConvoyerTile::DownEnd;
        } else if (startDir.y < 0) {
            if (endDir.y < 0) return ConvoyerTile::TopEnd;
        }
    }

    // Basic cases
    if (startDir.x > 0) {
        if (endDir.x > 0) return ConvoyerTile::Right;
        if (endDir.y > 0) return ConvoyerTile::RightDown;
        if (endDir.y < 0) return ConvoyerTile::RightTop;
    } else if (startDir.x < 0) {
        if (endDir.x < 0) return ConvoyerTile::Left;
        if (endDir.y > 0) return ConvoyerTile::LeftDown;
        if (endDir.y < 0) return ConvoyerTile::LeftTop;
    } else if (startDir.y > 0) {
        if (endDir.y > 0) return ConvoyerTile::Down;
        if (endDir.x > 0) return ConvoyerTile::DownRight;
        if (endDir.x < 0) return ConvoyerTile::DownLeft;
    } else if (startDir.y < 0) {
        if (endDir.y < 0) return ConvoyerTile::Top;
        if (endDir.x > 0) return ConvoyerTile::TopRight;
        if (endDir.x < 0) return ConvoyerTile::TopLeft;
    }

    // Invalid tile settings
    return ConvoyerTile::Invalid;
}