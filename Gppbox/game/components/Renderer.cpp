#include "Renderer.hpp"
#include "game/core/object/Object.hpp"

Renderer::Renderer(Object* obj, std::string text) : Renderer(obj, text, "res/simple.vert", "res/simple.frag") {}
Renderer::Renderer(Object* obj, std::string text, std::string vert, std::string frag) : Component(obj)
{
	manageTexture = true;
	manageShape = true;
	this->shape = new sf::RectangleShape(sf::Vector2f(1.0f, 1.0f));
	this->texture = new sf::Texture();
	isValid = texture->loadFromFile(text);
	init(vert, frag);
}

Renderer::Renderer(Object* obj, sf::Texture* text) : Renderer(obj, text, "res/simple.vert", "res/simple.frag") {}
Renderer::Renderer(Object* obj, sf::Texture* text, std::string vert, std::string frag) : Component(obj)
{
	manageTexture = false;
	manageShape = true;
	this->shape = new sf::RectangleShape(sf::Vector2f(1.0f, 1.0f));
	this->texture = text;
	isValid = true;
	init(vert, frag);
}

Renderer::Renderer(Object* obj, sf::Shape* shape, std::string text) : Renderer(obj, shape, text, "res/simple.vert", "res/simple.frag") { }
Renderer::Renderer(Object* obj, sf::Shape* shape, std::string text, std::string vert, std::string frag) : Component(obj)
{
	manageTexture = true;
	manageShape = false;
	this->shape = shape;
	this->texture = new sf::Texture();
	isValid = texture->loadFromFile(text);
	init(vert, frag);
}

Renderer::Renderer(Object* obj, sf::Shape* shape, sf::Texture* text) : Renderer(obj, shape, text, "res/simple.vert", "res/simple.frag") {}
Renderer::Renderer(Object* obj, sf::Shape* shape, sf::Texture* text, std::string vert, std::string frag) : Component(obj)
{
	manageTexture = false;
	manageShape = false;
	this->shape = shape;
	this->texture = text;
	isValid = true;
	init(vert, frag);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Renderer::init(std::string vert, std::string frag)
{
	if (!isValid) return;
	shape->setTexture(texture);
	//shader = new HotReloadShader(vert, frag);
}

Renderer::~Renderer()
{
	//if (isValid) delete shader;
	if (manageTexture) delete texture;
	if (manageShape) delete shape;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Renderer::update(double dt)
{
	// Update Shader
	if (!isValid) return;
	//shader->update(dt);
}

void Renderer::imgui()
{
	return;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Renderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!isValid) return;
	//shader->sh.setUniform("texture", texture);
	//states.shader = &shader->sh;
	states.transform *= getTransform();
	target.draw(*shape, states);
}