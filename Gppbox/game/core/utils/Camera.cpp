#include "Camera.hpp"
#include "engine/utils/Dice.hpp"
#include "game/core/object/Object.hpp"
#include "game/core/World.hpp"
#include "app/C.hpp"

Camera::Camera(World* world, sf::Vector2f center, sf::Vector2f size) : m_throttle(0.016f)
{
	this->world = world;
	m_view = sf::View(center, size);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Camera::update(double dt)
{
	Object* player = world->getPlayer();
	if (!player) return;

	sf::Vector2f shake = processShake(dt);
	sf::Vector2f pos = player->getPosition();
	//float x = (player->cx + player->rx) * C::GRID_SIZE + shake.x;
	//float y = (player->cy + player->ry - 2.5f) * C::GRID_SIZE + shake.y;
	m_view.setCenter(pos.x + shake.x, pos.y + shake.y);
}

void Camera::imgui()
{
	return;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


sf::Vector2f Camera::processShake(double dt)
{
	float radius = 0.0f;
	for (auto it = m_shakes.begin(); it != m_shakes.end();) {
		it->duration -= (float)dt;
		if (it->duration > 0.0f) {
			radius += it->intensity;
			++it;
		} else it = m_shakes.erase(it);
	}

	radius = std::min(radius, 100.0f); // avoid too much shaking
	if (radius > 0) {
		if (m_throttle.shouldExecute(dt)) {
			return sf::Vector2f(
				(Dice::randF() * 2.0f - 1.0f) * radius,
				(Dice::randF() * 2.0f - 1.0f) * radius
			);
		}
	}

	return sf::Vector2f(0.0f, 0.0f);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Camera::addShake(float duration, float intensity)
{
	m_shakes.push_back({ duration, intensity });
}

void Camera::setActive(sf::RenderTarget& win) const
{
	win.setView(m_view);
}