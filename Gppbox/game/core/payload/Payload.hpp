#pragma once

namespace sf {
	class Drawable;
}

class PayloadPool;
class PayloadBase;
typedef PayloadBase Payload;

class PayloadBase
{
private:
	friend class PayloadPool;
	bool pool = false;
	PayloadBase() : pool(true) { }

public:
	int quantity = -1;
	sf::Drawable* render = nullptr;
	PayloadBase(int qty) : quantity(qty), render(nullptr) { }
	PayloadBase(int qty, sf::Drawable* render) : quantity(qty), render(render) { }
};
