#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceType.hpp"

class RessourceSprite
{
private:
	class Cache
	{
	private:
		sf::Texture* texture;
	public:
		sf::Drawable* drawable;

		Cache(sf::Texture* texture, sf::Drawable* drawable)
			: texture(texture), drawable(drawable) { }

		~Cache()
		{
			delete texture;
			delete drawable;
		}
	};

	static inline std::map<ResourceType, Cache*> cacheMap;
	static inline sf::Drawable* fallback;

public:
	static void init();
	static void clear();
	static sf::Drawable* get(ResourceType type);

private:
	static Cache* cache(ResourceType type);
	static std::string getPath(ResourceType type);
};
