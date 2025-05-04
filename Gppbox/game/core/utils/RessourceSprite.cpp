#include "RessourceSprite.hpp"

void RessourceSprite::init()
{
	sf::RectangleShape* shape = new sf::RectangleShape({ 0.8f, 0.8f });
	shape->setFillColor(sf::Color::Magenta);
	fallback = static_cast<sf::Drawable*>(shape);
}

void RessourceSprite::clear()
{
	delete fallback;
	for (auto& itr : cacheMap)
		delete itr.second;
	cacheMap.clear();
}

sf::Drawable* RessourceSprite::get(ResourceType type)
{
	std::map<ResourceType, Cache*>::const_iterator itr = cacheMap.find(type);
	if (itr != cacheMap.end()) return itr->second->drawable;
	Cache* cache = RessourceSprite::cache(type);
	return cache == nullptr ? fallback : cache->drawable;
}

RessourceSprite::Cache* RessourceSprite::cache(ResourceType type)
{
	// Get path & check it
	std::string path = RessourceSprite::getPath(type);
	if (path == "Error") return nullptr;
	
	// Create drawable + it's texture & load it
	sf::RectangleShape* drawable = new sf::RectangleShape({ 1.0f, 1.0f });
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	drawable->setTexture(texture);

	// Create cache & return it
	Cache* cache = new Cache(texture, drawable);
	cacheMap.insert({ type, cache });
	return cache;
}

std::string RessourceSprite::getPath(ResourceType type)
{
	switch (type) {
		case ResourceType::Wood: return "assets/rs/wood.png";
		case ResourceType::Planks: return "assets/rs/planks.png";
	}
	return "Error";
}