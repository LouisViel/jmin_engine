#pragma once

#include <string>
#include "Component.hpp"
#include "engine/core/HotReloadShader.hpp"

class Renderer : public Component, public sf::Transformable
{
private:
	HotReloadShader* shader = nullptr;
	sf::Texture* texture = nullptr;
	bool manageTexture = false;
	bool manageShape = false;
	bool isValid = false;

public:
	sf::Shape* shape = nullptr;

public:
	Renderer(Object* obj, std::string text);
	Renderer(Object* obj, std::string text, std::string vert, std::string frag);

	Renderer(Object* obj, sf::Texture* text);
	Renderer(Object* obj, sf::Texture* text, std::string vert, std::string frag);

	Renderer(Object* obj, sf::Shape* shape, std::string text);
	Renderer(Object* obj, sf::Shape* shape, std::string text, std::string vert, std::string frag);

	Renderer(Object* obj, sf::Shape* shape, sf::Texture* text);
	Renderer(Object* obj, sf::Shape* shape, sf::Texture* text, std::string vert, std::string frag);

	void init(std::string vert, std::string frag);
	~Renderer();

	void update(double dt) override;
	void imgui() override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
