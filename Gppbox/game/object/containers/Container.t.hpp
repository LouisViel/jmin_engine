#pragma once
#include "ContainerBase.hpp"

template <typename t>
class Container : public ContainerBase
{
protected:
	InOutConvoyHandle<t>* inputHandle = nullptr;

public:
	Container(ResourceType type, sf::Vector2f colliderSize);
	virtual ~Container() { return; }

	void update(double dt) override;
};

