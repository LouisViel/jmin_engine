#include "Convoyer.hpp"

Convoyer::Convoyer()
{
    tilemap = new TileMap();
}

Convoyer::~Convoyer()
{
    delete tilemap;
}

void Convoyer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*tilemap, states);
    // TODO : Draw items on top of convoyer
}