#pragma once
#include "SFML/Graphics.hpp"
#include "app/C.hpp"

class ScaleHelper
{
private:
	class ScaleApply : public sf::Transformable {};
	static ScaleHelper* singleton;
	ScaleApply inverter;
	ScaleApply applier;

public:
	ScaleHelper() {
		constexpr float grid = float(C::GRID_SIZE);
		constexpr float gridInverse = float(1.0f / C::GRID_SIZE);
		this->inverter.setScale(gridInverse, gridInverse);
		this->applier.setScale(grid, grid);
		singleton = this;
	}

	static const sf::Transform& apply() {
		return singleton->applier.getTransform();
	}

	static const sf::Transform& invert() {
		return singleton->inverter.getTransform();
	}
};