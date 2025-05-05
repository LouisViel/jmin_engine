#include "SpriteHelper.hpp"

void SpriteHelper::init()
{
	sf::RectangleShape* shape = new sf::RectangleShape({ 0.8f, 0.8f });
	shape->setFillColor(sf::Color::Magenta);
	fallback = static_cast<sf::Drawable*>(shape);
}

void SpriteHelper::clear()
{
	delete fallback;
	for (auto& itr : cacheMap)
		delete itr.second;
	cacheMap.clear();
}

sf::Drawable* SpriteHelper::get(SpriteStatic type)
{
	std::map<SpriteStatic, Cache*>::const_iterator itr = cacheMap.find(type);
	if (itr != cacheMap.end()) return itr->second->drawable;
	Cache* cache = SpriteHelper::cache(type);
	return cache == nullptr ? fallback : cache->drawable;
}

SpriteHelper::Cache* SpriteHelper::cache(SpriteStatic type)
{
	// Get path & check it
	std::string path = SpriteHelper::getPath(type);
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

std::string SpriteHelper::getPath(SpriteStatic type)
{
	switch (type) {
		case SpriteStatic::ConvoyInput_Up: return "assets/convoy/input_up.png";
		case SpriteStatic::ConvoyInput_Down: return "assets/convoy/input_down.png";
		case SpriteStatic::ConvoyOutput_Up: return "assets/convoy/output_up.png";
		case SpriteStatic::ConvoyOutput_Down: return "assets/convoy/output_down.png";
	}
	return "Error";
}