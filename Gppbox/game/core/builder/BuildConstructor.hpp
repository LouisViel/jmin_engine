#pragma once
#include <SFML/Graphics.hpp>
#include "game/core/object/CollisionTester.hpp"

class Object;
class Game;

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
	bool isDrawValid = true;
	bool isConvoyer() const { return buildType == BuildType::Convoyer; }
	bool isBuilding() const { return buildType == BuildType::Building; }


public:
	virtual ~BuildConstructor() { }

	// Try destroy what is preventing from building at this position
	virtual void destroyAt(Game* game);

	// Check if constructor can build here (does not ensure it will not fail however)
	virtual bool canBuild(Game* game) = 0;

	// Try Build. If doing a step or not possible, return nullptr
	virtual Object* tryBuild() = 0;

	// Save cursor target position (default -> setPosition)
	virtual void setTargetPosition(sf::Vector2i pos);

	// Handle Inputs for custom constructors
	virtual void handleInputs() { };

	BuildConstructor* constructor() { return static_cast<BuildConstructor*>(this); }

protected:
	void applyTransform(sf::RenderStates& states) const;
	void copyTransformTo(sf::Transformable* other) const;
};