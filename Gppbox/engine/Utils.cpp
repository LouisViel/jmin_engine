#include <cmath>
#include "Utils.hpp"
#include "game/core/object/Object.hpp"
#include "game/core/object/Collider.hpp"
#include "app/M.hpp"

bool Utils::isFullBody(const Object* object, int gridx, int gridy)
{
    FULL_CHECK(object, (xpos == gridx && int(ypos) == gridy));
}

bool Utils::isAdjacent(const sf::Vector2i& a, const sf::Vector2i& b)
{
    return (
        (a.x == b.x && (a.y - 1 == b.y || a.y + 1 == b.y)) ||
        (a.y == b.y && (a.x - 1 == b.x || a.x + 1 == b.x))
    );
}



int Utils::safeAdd(int val, int add) {
    return std::min(val, maxInt - add) + add;
}

int Utils::safeMinus(int val, int min) {
    return std::max(val, minInt + min) - min;
}



float Utils::toLength(const sf::Vector2i& source)
{
    return (float)sqrt((source.x * source.x) + (source.y * source.y));
}

float Utils::toLength(const sf::Vector2f& source)
{
    return sqrt((source.x * source.x) + (source.y * source.y));
}

float Utils::toAngle(const sf::Vector2i& source)
{
    float angle = (float)atan2(source.y, source.x);
    if (angle < 0.0f) angle += float(M_PI + M_PI);
    return float(angle * RadToDeg);
}

float Utils::toAngle(const sf::Vector2f& source)
{
    float angle = atan2(source.y, source.x);
    if (angle < 0.0f) angle += float(M_PI + M_PI);
    return float(angle * RadToDeg);
}

sf::Vector2f Utils::fromAngle(float angle)
{
    float rad = float(angle * DegToRad);
    return normalize(sf::Vector2f {
        cos(rad),
        sin(rad)
    });
}




sf::Vector2f Utils::normalize(const sf::Vector2i& source)
{
    float length = toLength(source);
    if (length != 0) return sf::Vector2f(source.x / length, source.y / length);
    else return sf::Vector2f((float)source.x, (float)source.y);
}

sf::Vector2f Utils::normalize(const sf::Vector2f& source)
{
    float length = toLength(source);
    if (length != 0) return sf::Vector2f(source.x / length, source.y / length);
    else return source;
}

sf::Vector2i Utils::rotate(const sf::Vector2i& source, float angle)
{
    float length = toLength(source);
    float target = fmod(toAngle(source) + angle, 360.0f);
    sf::Vector2f res = fromAngle(target) * length;
    return sf::Vector2i{ int(round(res.x)), int(round(res.y)) };
}

sf::Vector2f Utils::rotate(const sf::Vector2f& source, float angle)
{
    float length = toLength(source);
    float target = fmod(toAngle(source) + angle, 360.0f);
    return fromAngle(target) * length;
}





float Utils::lerp(float a, float b, float f)
{
    return a * (1.0f - f) + (b * f);
}

float Utils::lerp(int a, int b, float f)
{
    return Utils::lerp((float)a, (float)b, f);
}

sf::Vector2f Utils::lerp(const sf::Vector2f& a, const sf::Vector2f& b, float f)
{
    return sf::Vector2f(Utils::lerp(a.x, b.x, f), Utils::lerp(a.y, b.y, f));
}

sf::Vector2f Utils::lerp(const sf::Vector2i& a, const sf::Vector2i& b, float f)
{
    return sf::Vector2f(Utils::lerp(a.x, b.x, f), Utils::lerp(a.y, b.y, f));
}