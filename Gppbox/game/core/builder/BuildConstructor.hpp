#pragma once
#include <SFML/Graphics.hpp>

class Object;

class BuildConstructor : public sf::Drawable, public sf::Transformable
{
protected:
	enum class BuildType
	{
		Unknown = 0,
		Convoyer = 1,
		Building = 2
	};

protected:
	BuildType buildType = BuildType::Unknown;

public:
	bool isConvoyer() const { return buildType == BuildType::Convoyer; }
	bool isBuilding() const { return buildType == BuildType::Building; }
	virtual Object* build() = 0;
};