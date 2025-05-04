#include "Convoyer.hpp"
#include "engine/Utils.hpp"
#include "engine/utils/TransformHelper.hpp"


Convoyer::Convoyer() : Convoyer(speed) {}

Convoyer::Convoyer(float speed) : speed(speed)
{
    // Setup Input Handle (with default settings) (Need to be updated later)
    inputHandle = new InOutConvoyDefault(InOutConvoy::Mode::In, ResourceTypeHelper::All, DirectionHelper::All);
    inputHandle->anchor = sf::Vector2i(0, 0);
    inputHandle->managePayload = false;

    // Setup Output Handle (with default settings) (Need to be updated later)
    outputHandle = new InOutConvoyDefault(InOutConvoy::Mode::Out, ResourceTypeHelper::All, DirectionHelper::All);
    outputHandle->anchor = sf::Vector2i(0, 0);
    outputHandle->managePayload = false;

    // Setup convoyer parts & items containers
    parts = new std::vector<sf::Vector2i>();
    items = new std::vector<ConvoyerItem*>();

    // Setup rendering
    tilemap = new TileMap();
    if (!tilemap->load(C::CONVOYER_TILESET))
        printf("Could not load convoyer tileset !\n");
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

size_t Convoyer::size()
{
    return parts->size();
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool Convoyer::connectInput(InOutConvoy* const input)
{
    if (inputHandle->payload != nullptr) return false;
    if (!inputHandle->connect(*input)) return false;
    InOutConvoyDefault* inputBase = input->handle<PayloadBase>();
    if (inputBase->payload == nullptr) return false;
    inputHandle->payload = inputBase->payload;
    inputHandle->connected = true;
    return true;
}

bool Convoyer::connectOutput(InOutConvoy* const output)
{
    if (outputHandle->payload != nullptr) return false;
    if (!outputHandle->connect(*output)) return false;
    InOutConvoyDefault* outputBase = output->handle<PayloadBase>();
    if (outputBase->payload == nullptr) return false;
    outputHandle->payload = outputBase->payload;
    outputHandle->connected = true;
    return true;
}

void Convoyer::removeInput()
{
    if (inputHandle->payload == nullptr) return;
    inputHandle->payload = nullptr;
    inputHandle->connected = false;
}

void Convoyer::removeOutput()
{
    if (outputHandle->payload == nullptr) return;
    outputHandle->payload = nullptr;
    outputHandle->connected = false;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Convoyer::buildWorld(sf::Vector2i startPos, sf::Vector2i endPos, std::vector<sf::Vector2i>& tiles, bool convertTiles)
{
    // Get converter (transform)
    const sf::Vector2f& pos = getPosition();
    const sf::Vector2i convoyerPos = sf::Vector2i((int)pos.x, (int)pos.y);

    // Convert positions to local coordinates
    sf::Vector2i startWorld = startPos - convoyerPos;
    sf::Vector2i endWorld = endPos - convoyerPos;
    std::vector<sf::Vector2i> tilesWorld = std::vector<sf::Vector2i>();
    if (convertTiles) for (sf::Vector2i tile : tiles) tilesWorld.push_back(tile - convoyerPos);
    else tilesWorld.insert(tilesWorld.begin(), tiles.begin(), tiles.end());

    // Call local coordinates build
    this->build(startWorld, endWorld, tilesWorld);
}

void Convoyer::expandWorld(sf::Vector2i endPos, std::vector<sf::Vector2i>& tiles, bool convertTiles)
{
    // Get converter (transform)
    const sf::Vector2f& pos = getPosition();
    const sf::Vector2i convoyerPos = sf::Vector2i((int)pos.x, (int)pos.y);

    // Convert positions to local coordinates
    sf::Vector2i endWorld = endPos - convoyerPos;
    std::vector<sf::Vector2i> tilesWorld = std::vector<sf::Vector2i>();
    if (convertTiles) for (sf::Vector2i tile : tiles) tilesWorld.push_back(tile - convoyerPos);
    else tilesWorld.insert(tilesWorld.begin(), tiles.begin(), tiles.end());

    // Call local coordinates expand
    this->expand(endWorld, tilesWorld);
}

void Convoyer::removeWorld(sf::Vector2i cutPos)
{
    // Get converter (transform)
    const sf::Vector2f& pos = getPosition();
    const sf::Vector2i convoyerPos = sf::Vector2i((int)pos.x, (int)pos.y);

    // Convert positions to local coordinates
    sf::Vector2i cutWorld = cutPos - convoyerPos;

    // Call local coordinates expand
    this->remove(cutWorld);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Convoyer::build(sf::Vector2i startPos, sf::Vector2i endPos, std::vector<sf::Vector2i>& tiles)
{
    // Prevent weird invocation of build method
    if (tiles.size() <= 0) throw std::exception("Cannot build a convoyer without tiles");

    // Initialize tilemap with specified settings
    const unsigned int gridSize = (unsigned int)C::GRID_SIZE;
    sf::Vector2u tileSize = sf::Vector2u(gridSize, gridSize);
    tilemap->init(tileSize, (unsigned int)tiles.size());
    
    // Register part settings
    this->multiPart = tiles.size() > 2;

    // Set Start part (special treatment)
    sf::Vector2i startTile = tiles[0]; // Should always be sf::Vectori(0, 0)
    sf::Vector2i targetTile = multiPart ? tiles[1] : endPos;
    tilemap->setPos(0, startTile.x, startTile.y);
    tilemap->setTile(0, &getTile(startPos, startTile, targetTile, 1));

    // Set intermediate parts (basic treatments)
    for (int i = 1; i < (int)tiles.size() - 2; ++i) {
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
        sf::Vector2i prevTile = tiles[idEnd - 1];
        sf::Vector2i endTile = tiles[idEnd];
        tilemap->setPos(idEnd, endTile.x, endTile.y);
        tilemap->setTile(idEnd, &getTile(prevTile, endTile, endPos, 2));
    } outputHandle->anchor = tiles.back();

    // Register parts of convoyer
    parts->clear();
    parts->insert(parts->begin(), tiles.begin(), tiles.end());
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Convoyer::expand(sf::Vector2i endPos, std::vector<sf::Vector2i>& tiles)
{
    // Prevent weird invocations of build method
    if (parts->size() <= 0) throw std::exception("Cannot expand a non constructed convoyer");
    if (tiles.size() <= 0) throw std::exception("Cannot expand a convoyer without tiles");

    // Save indexs, insert tiles, resize tilemap
    size_t expandIndex = parts->size();
    size_t resultSize = expandIndex + tiles.size();
    parts->insert(parts->end(), tiles.begin(), tiles.end());
    tilemap->resize((unsigned int)resultSize);

    // Update previous end part
    if (multiPart) {
        size_t prevEndId = expandIndex - 1;
        sf::Vector2i prevTile = prevEndId > 0 ? parts->operator[](prevEndId - 1) : sf::Vector2i(0, 0);
        sf::Vector2i prevEndTile = parts->operator[](prevEndId);
        sf::Vector2i targetTile = parts->operator[](expandIndex);
        tilemap->setTile(prevEndId, &getTile(prevTile, prevEndTile, targetTile));
    }

    // Register part settings
    this->multiPart = resultSize > 2;

    // Set intermediate parts (basic treatments)
    for (int i = (int)expandIndex; i < (int)resultSize - 2; ++i) {
        size_t id = static_cast<size_t>(i);
        sf::Vector2i& previousTile = parts->operator[](id - 1);
        sf::Vector2i& tile = parts->operator[](id);
        sf::Vector2i& nextTile = parts->operator[](id + 1);
        tilemap->setPos(id, tile.x, tile.x);
        tilemap->setTile(id, &getTile(previousTile, tile, nextTile));
    }

    // Set End part (special treatment)
    if (multiPart) {
        size_t idEnd = resultSize - 1;
        sf::Vector2i prevTile = parts->operator[](idEnd - 1);
        sf::Vector2i endTile = parts->operator[](idEnd);
        tilemap->setTile(idEnd, &getTile(prevTile, endTile, endPos, 2));
        outputHandle->anchor = endTile;
    } else outputHandle->anchor = sf::Vector2i(0, 0);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Convoyer::remove(size_t partsCount)
{
    // Calculate new size & verify it
    size_t newSize = std::max((size_t)0, parts->size() - partsCount);
    if (newSize == parts->size()) return;
    sf::Vector2i endPos = parts->operator[](newSize);

    // Resize tilemap & parts containers
    if (newSize <= 0) parts->clear();
    else parts->resize(newSize);
    tilemap->resize((unsigned int)newSize);

    // Register part settings
    this->multiPart = newSize > 2;

    // Update cut part as an end part
    if (multiPart) {
        size_t idEnd = newSize - 1;
        sf::Vector2i prevTile = parts->operator[](idEnd - 1);
        sf::Vector2i endTile = parts->operator[](idEnd);
        tilemap->setTile(idEnd, &getTile(prevTile, endTile, endPos, 2));
        outputHandle->anchor = endTile;
    } else outputHandle->anchor = sf::Vector2i(0, 0);

    // Remove/Destroy items which were after the cut part
    float maxProgression = (float)newSize - 0.001f;
    LOOPB_PTR(items, ConvoyerItem* item);
    if (item->progression >= maxProgression) {
        items->erase(items->begin() + i);
        PayloadPool::free(item->payload);
        ConvoyerItemPool::free(item);
    }
    LOOP_END;

    // Force remove handles
    if (newSize <= 0) removeInput();
    removeOutput();
}

void Convoyer::remove(sf::Vector2i cutPos)
{
    // Search for cut pos index
    int index = -1;
    LOOPB_PTR(parts, sf::Vector2i& part);
    if (part == cutPos) {
        index = i;
        break;
    }
    LOOP_END;

    // Invoke remove on corresponding count
    if (index >= 0) remove(parts->size() - index);
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
    if (inputHandle->payload != nullptr) {
        #pragma warning(suppress:6011)
        while (inputHandle->payload->valid() && (previous == nullptr || previous->progression - 1.0f >= 0.0f)) {
            ConvoyerItem* item = ConvoyerItemPool::get(inputHandle->payload->pop());
            if (!processItem(previous, item, partSize, fdt)) {
                items->emplace_back(item);
                previous = item;
            } else ConvoyerItemPool::free(item);
        }
    }
}

bool Convoyer::processItem(ConvoyerItem* previous, ConvoyerItem* item, float partSize, float dt)
{
    // Update progression + Push to output buffer if reached & possible
    item->progression += dt * speed;
    if (previous != nullptr) item->progression = std::min(item->progression, previous->progression - 1.0f);
    if (item->progression >= partSize) {
        item->progression = partSize;
        if (outputHandle->payload == nullptr) return false;
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

    // Render convoyer & setup for items
    Object::applyTransform(states);
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

bool Convoyer::isCollision(int gridx, int gridy) const
{
    sf::Vector2f position = getPosition();
    sf::Vector2i pos = sf::Vector2i((int)position.x, (int)position.y);
    sf::Vector2i gridPos = sf::Vector2i(gridx, gridy);
    
    for (sf::Vector2i& part : *parts) {
        if (pos + part == gridPos) return true;
    }
    return false;
}

std::vector<sf::Vector2i> Convoyer::getCollisions() const
{
    sf::Vector2f position = getPosition();
    sf::Vector2i pos = sf::Vector2i((int)position.x, (int)position.y);

    std::vector<sf::Vector2i> collisions = std::vector<sf::Vector2i>();
    collisions.reserve(parts->size());

    for (sf::Vector2i& part : *parts)
        collisions.emplace_back(pos + part);
    return collisions;
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