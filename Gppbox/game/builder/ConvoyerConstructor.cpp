#include <SFML/Graphics.hpp>
#include "ConvoyerConstructor.hpp"
#include "game/object/convoyer/Convoyer.hpp"
#include "game/core/Game.hpp"
#include "game/core/World.hpp"
#include "engine/utils/Bresenham.hpp"
#include "engine/utils/InputHandler.hpp"

// TODO : IMPORTANT !!!!!
// TODO : reword plus tard pour pouvoir reprendre un convoyer partiellement construit (là obligé d'aller jusqu'au bout)


ConvoyerConstructor::ConvoyerConstructor()
{
	this->buildType = BuildType::Convoyer;
	inputConvoy = new InOutConvoy(InOutConvoy::Mode::In, ResourceTypeHelper::All, DirectionHelper::All);
	outputConvoy = new InOutConvoy(InOutConvoy::Mode::Out, ResourceType::Unknown, DirectionHelper::All);
}

ConvoyerConstructor::~ConvoyerConstructor()
{
	if (convoyer != nullptr) delete convoyer;
	delete inputConvoy;
	delete outputConvoy;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool ConvoyerConstructor::canBuild(Game* game)
{
	// First Phase : Create convoyer (start)
	if (state == State::Create) {
		// Check if position is buildable
		if (!game->isBuildable(NodeType::None, cursorPos.x, cursorPos.y)) {
			currentConvoy = nullptr;
			return false;
		}
		// Get building output convoy to link as input to this convoyer
		currentConvoy = game->world->getBuildingOutput(cursorPos, inputConvoy);
		return currentConvoy != nullptr;
	}
	

	// Second Phase : Try to bresenham convoyer path to extend it
	if (state == State::Extend || state == State::Finish) {
		// Check if tiles are buildables
		if (bresenTiles.size() <= 0) return false;
		for (sf::Vector2i& tile : bresenTiles) {
			if (!game->isBuildable(NodeType::None, tile.x, tile.y)) {
				currentConvoy = nullptr;
				return false;
			}
		}

		// Manage special case 'finish state'
		if (state == State::Finish) {
			// Get current output convoy & confirm can build this final extension
			currentConvoy = game->world->getBuildingInput(currentAnchor, outputConvoy);
			return true;
		}

		// Can build this extension
		return true;
	}

	// Should never happen
	return false;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


Object* ConvoyerConstructor::tryBuild()
{
	// Process at convoyer creation
	if (state == State::Create) {
		state = State::Extend;

		// Save settings for expand & Output connection
		outputConvoy->type = currentConvoy->type;
		currentAnchor = cursorPos;

		// Create & set convoyer settings
		convoyer = new Convoyer(speed);
		Game::singleton->world->previews->push_back(convoyer);
		BuildConstructor::copyTransformTo(convoyer);

		// Calculate pos utils
		sf::Vector2i startPos = currentConvoy->worldPos + currentConvoy->anchor;
		sf::Vector2i endPos = cursorPos + (cursorPos - startPos);

		// Build convoyer internal
		std::vector<sf::Vector2i> convoyers = { sf::Vector2i(0, 0) };
		convoyer->buildWorld(startPos, endPos, convoyers, false);
		convoyer->connectInput(currentConvoy);

		// Construction not finished, going to next state
		return nullptr;
	}

	// Process at convoyer extention
	if (state == State::Extend || state == State::Finish) {

		// Expand convoyer internal
		size_t tilesSize = bresenTiles.size();
		sf::Vector2i previousPos = tilesSize >= 2 ? bresenTiles[tilesSize - 2] : currentAnchor;
		sf::Vector2i tilePos = bresenTiles[tilesSize - 1];
		sf::Vector2i endPos = tilePos + (tilePos - previousPos);
		convoyer->expandWorld(endPos, bresenTiles);

		// Save settings
		currentAnchor = cursorPos;

		// Manage special case 'finish state'
		if (state == State::Finish) {
			// finish construction of convoyer & setup it
			if (currentConvoy != nullptr) convoyer->connectOutput(currentConvoy);
			Game::singleton->world->removePreview(convoyer);

			// Reset settings & return convoyer
			Object* result = static_cast<Object*>(convoyer);
			outputConvoy->type = ResourceType::Unknown;
			convoyer = nullptr;
			bresenTiles.clear();
			state = State::Create;
			return result;
		}

		// Construction not finished, waiting for validation (state finish)
		return nullptr;
	}

	// Should never happen
	return nullptr;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void ConvoyerConstructor::setTargetPosition(sf::Vector2i pos)
{
	// Save cursor pos
	cursorPos = pos;

	// Manage State Create case
	if (state == State::Create) {
		BuildConstructor::setTargetPosition(cursorPos);
		return;
	}

	// Manage State Extend case
	if (state == State::Extend || state == State::Finish) {
		bresenTiles.clear();
		bresenhamLine(currentAnchor.x, currentAnchor.y, cursorPos.x, cursorPos.y, bresenTiles);
		return;
	}
}

void ConvoyerConstructor::handleInputs()
{
	bool tryChange = InputHandler::getJump();
	if (!tryChange) return;
	if (state == State::Extend) state = State::Finish;
	else if (state == State::Finish) state = State::Extend;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void ConvoyerConstructor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (state == State::Create) {
		
		sf::RectangleShape spr = sf::RectangleShape({ 0.95f, 0.95f });
		spr.setFillColor(isDrawValid ? sf::Color::Green : sf::Color::Red);
		spr.setOutlineColor(isDrawValid ? sf::Color::Blue : sf::Color::Yellow);
		spr.setOutlineThickness(0.05f);
		//spr.setOrigin({ C::GRID_SIZE * 0.5f, C::GRID_SIZE * 2 });

		// Draw create convoyer preview
		BuildConstructor::applyTransform(states);
		//spr.setPosition((float)cursorPos.x, (float)cursorPos.y);
		target.draw(spr, states);
		return;
	}


	// Ensure convoyer exist
	if (convoyer == nullptr) return;


	// Draw convoyer preview
	// No need to 'apply transform', will be handled by convoyer itself
	target.draw(*convoyer, states);
	BuildConstructor::applyTransform(states);


	// Draw convoyer extand preview
	if (state == State::Extend || state == State::Finish) {

		sf::RectangleShape spr = sf::RectangleShape({ 0.95f, 0.95f });
		spr.setFillColor(isDrawValid ? sf::Color::Green : sf::Color::Red);
		spr.setOutlineColor(isDrawValid ? sf::Color::Blue : sf::Color::Yellow);
		spr.setOutlineThickness(0.05f);
		//spr.setOrigin({ C::GRID_SIZE * 0.5f, C::GRID_SIZE * 2 });

		// Draw bresenham convoyer tiles previews
		sf::Vector2f position = convoyer->getPosition();
		sf::Vector2i pos = sf::Vector2i((int)position.x, (int)position.y);
		for (sf::Vector2i tile : bresenTiles) {
			sf::Vector2i localPos = tile - pos;
			spr.setPosition((float)localPos.x, (float)localPos.y);
			target.draw(spr, states);
		}
	}
}