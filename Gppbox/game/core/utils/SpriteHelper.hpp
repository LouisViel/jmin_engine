#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceType.hpp"

enum class SpriteStatic : int
{
	ConvoyInput_Up,
	ConvoyInput_Down,
	ConvoyOutput_Up,
	ConvoyOutput_Down,
};

class SpriteHelper
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

	static inline std::map<SpriteStatic, Cache*> cacheMap;
	static inline sf::Drawable* fallback;

public:
	static void init();
	static void clear();
	static sf::Drawable* get(SpriteStatic type);

private:
	static Cache* cache(SpriteStatic type);
	static std::string getPath(SpriteStatic type);
};
