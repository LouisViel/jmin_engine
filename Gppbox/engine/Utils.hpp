#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "SFML/System/Vector2.hpp"

class Object;

class Utils
{
private:
	#define RadToDeg (180.0f / M_PI)
	#define DegToRad (M_PI / 180.0f)

public:
	static bool isFullBody(Object* object, int gridx, int gridy);
	template <typename T> static int sign(T value);

	static float toLength(const sf::Vector2i& source);
	static float toLength(const sf::Vector2f& source);
	static float toAngle(const sf::Vector2i& source);
	static float toAngle(const sf::Vector2f& source);
	static sf::Vector2f fromAngle(float angle);

	static sf::Vector2f normalize(const sf::Vector2i& source);
	static sf::Vector2f normalize(const sf::Vector2f& source);
	static sf::Vector2i rotate(const sf::Vector2i& source, float angle);
	static sf::Vector2f rotate(const sf::Vector2f& source, float angle);

	static float lerp(float a, float b, float f);
	static float lerp(int a, int b, float f);
	static sf::Vector2f lerp(const sf::Vector2f& source, const sf::Vector2f& target, float t);
	static sf::Vector2f lerp(const sf::Vector2i& source, const sf::Vector2i& target, float t);
};

template <typename T>
int Utils::sign(T val) {
	return (T(0) < val) - (val < T(0));
}