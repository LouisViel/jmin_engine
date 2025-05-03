#pragma once
#include "game/core/builder/BuildConstructor.hpp"
#include "game/core/payload/InOutConvoy.hpp"
#include "game/object/convoyer/Convoyer.hpp"

class ConvoyerConstructor : public BuildConstructor
{
protected:
	enum class State : int
	{
		Create = 0,
		Extend = 1,
		Finish = 2
	};

private:
	InOutConvoy* inputConvoy = nullptr;
	InOutConvoy* outputConvoy = nullptr;
	std::vector<sf::Vector2i> bresenTiles;

	State state = State::Create;
	Convoyer* convoyer = nullptr;
	InOutConvoy* currentConvoy = nullptr;

	sf::Vector2i currentAnchor = sf::Vector2i(0, 0);
	sf::Vector2i cursorPos = sf::Vector2i(0, 0);

public:
	float speed = 1.0f;

public:
	ConvoyerConstructor();
	virtual ~ConvoyerConstructor();

	bool canBuild(Game* game) override;
	Object* tryBuild() override;

	void setTargetPosition(sf::Vector2i pos) override;
	void handleInputs() override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};
