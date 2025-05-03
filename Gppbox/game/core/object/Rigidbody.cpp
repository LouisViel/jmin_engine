#include "Rigidbody.hpp"
#include "Object.hpp"
#include "game/core/Game.hpp"
#include "app/C.hpp"

Rigidbody::Rigidbody(Object* _object) : gameobject(_object)
{

}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Rigidbody::processMovement(double fdt)
{
	Game& g = *Game::singleton;
	double rate = 1.0 / fdt; // How many times in 1 second (1 second / deltatime)
	double dfr = C::F_REF / rate; // Normalize rate from framerate

	// Apply Frictions
	dx *= pow(frx, (float)dfr);
	dy *= pow(fry, (float)dfr);

	// Process raw movement
	float _rx = rx + dx * (float)fdt; // Calculate internal movement x
	float _ry = ry + dy * (float)fdt; // Calculate internal movement y

	// Reset Collisions
	hcollision = 0;
	vcollision = 0;

	// Apply Physics & Collision check to results
	if (usePhysics) {
		processHorizontal(g, _rx, _ry);
		processVertical(g, _rx, _ry);

	// Update values without physics
	} else {
		float valx = std::fmod(_rx, 1.0f);
		cx += int(_rx - valx); _rx = valx;
		float valy = std::fmod(_ry, 1.0f);
		cy += int(_ry - valy); _ry = valy;
	}

	// Apply final results
	rx = _rx;
	ry = _ry;

	// Publish Transform to Object
	if (autoPublish) publishTransform();
}

void Rigidbody::publishTransform()
{
	gameobject->setPosition(
		float(cx + rx),
		float(cy + ry)
	);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Rigidbody::setDx(double dx)
{
	this->dx = (float)std::clamp(dx, -C::E_MAX_X, C::E_MAX_X);
}

void Rigidbody::setDy(double dy)
{
	this->dy = (float)std::clamp(dy, -C::E_MAX_Y, C::E_MAX_Y);
}

sf::Vector2i Rigidbody::getCollision()
{
	return sf::Vector2i(hcollision, vcollision);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void Rigidbody::processHorizontal(Game& g, float& _rx, const float& _ry)
{
	// No Process Needed
	if (dx == 0.0f) return;

	// Pre-Process Variables
	bool isCollision = false;
	int yposMax(int(ry - height));
	float xposMax(_rx + width), rxMax(rx + width);
	float xposMin(_rx - width), rxMin(rx - width);

	// Check & Need to process Right
	if (dx > 0.0f) {

		// Check if need to process collisions
		if (int(xposMax) > int(rxMax)) {
			// Check for right collisions // TODO : Ajouter une verif "anti-teleportation" (Normalisée grace au fixed-update)
			for (float xpos = _rx + cx, xtarget = xposMax + 1 + cx; xpos < xtarget && !isCollision; ++xpos) {
				for (float ypos = ry + cy, ytarget = float(yposMax + cy); ypos > ytarget && !isCollision; --ypos)
					isCollision = g.isOccupied((int)xpos, (int)ypos);
			}
		}
		

		// Blocked on Right by Collision
		if (isCollision) {
			dx = 0; // Cancel Move Speed
			_rx = rx; // Reset internal position x
			hcollision = 1;

		// Process movement on Right
		} else {
			// Update internal & full position x
			int rxi = int(_rx);
			cx += rxi;
			_rx -= rxi;
		}

		// End Horizontal Process
		return;
	}

	// Check & Need to process Left
	if (dx < 0.0f) {
		
		// Check if need to process collisions
		//if (int(xposMin) < int(rxMin)) {
			// Check for left collisions // TODO : Ajouter une verif "anti-teleportation" (Normalisée grace au fixed-update)
			for (float xpos = _rx + cx, xtarget = xposMin - 1 + cx; xpos > xtarget && !isCollision; --xpos) {
				for (float ypos = ry + cy, ytarget = float(yposMax + cy); ypos > ytarget && !isCollision; --ypos) {
					isCollision = g.isOccupied((int)xpos, (int)ypos);
				}
			}
		//}

		// Blocked on Left by Collision
		if (isCollision) {
			dx = 0; // Cancel Move Speed
			_rx = rx; // Reset internal position x
			hcollision = -1;

		// Process movement on Left
		} else if (_rx < 0.0f) {
			// Update internal & full position x
			int rxi((int)_rx);
			if (_rx - rxi != 0.0f) rxi -= 1;
			cx += rxi;
			_rx -= rxi;
		}

		// End Horizontal Process
		return;
	}
}

void Rigidbody::processVertical(Game& g, const float& _rx, float& _ry)
{
	// No Process Needed
	if (dy == 0.0f) return;

	// Pre-Process Variables
	bool isCollision = false;
	float xposMin(_rx - width);
	int xposMax(int(_rx + width + 1));
	float cry(cy + _ry);

	// Check & Need to process Down
	if (dy > 0.0f && _ry > 1.0f) {

		// Check for down collisions // TODO : Ajouter une verif "anti-teleportation" (Normalisée grace au fixed-update)
		for (float xpos = xposMin + cx, target = float(xposMax + cx);
			xpos < target && !isCollision; ++xpos
		) isCollision = g.isOccupied((int)xpos, (int)cry);

		// Process Is Grounded
		if (isCollision) {
			dy = 0.0f; // Cancel Movement y
			_ry = 0.99f; // Attach ry to ground
			vcollision = 1;

		// Process Gravity/Falling
		} else {
			// Update internal & full position y
			int ryi((int)_ry);
			cy += ryi;
			_ry -= ryi;
		}

		// End Vertical Process
		return;
	}

	
	// Check & Need to process Up
	if (dy < 0.0f) {
		// Invoke Grounded Callback

		// Check if need to process collisions
		if (int(_ry - height) != int(ry - height)) {
			// Check for up collisions (+ Allow single platform bypass) // TODO : Ajouter une verif "anti-teleportation" (Normalisée grace au fixed-update)
			for (float xpos = xposMin + cx, xtarget = float(xposMax + cx), collisionCount = 0; xpos < xtarget && !isCollision; ++xpos) {
				for (float ypos = cry, ytarget = cry - height - 1; ypos > ytarget && !isCollision; --ypos) {
					if (g.isOccupied((int)xpos, (int)ypos)) {
						if (++collisionCount > 1) isCollision = true;
					} else collisionCount = 0;
				}
			}
		}

		// Process se cogne la tete
		if (isCollision) {
			dy = 0.0f; // Cancel Movement y
			_ry = ry; // Reset ry at frame start state
			vcollision = -1;

		// Process Jumping/Flying
		} else if (_ry < 0.0f) {
			// Update internal & full position y
			int ryi((int)_ry);
			if (_ry - ryi != 0.0f) --ryi;
			cy += ryi;
			_ry -= ryi;
		}

		// End Vertical Process
		return;
	}
}
