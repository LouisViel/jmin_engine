#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

class Dice {
public:
	static int randSign() {
		return (rand() % 2) ? 1 : -1;
	}

	static int roll(int min, int max) {
		return min + rand() % (max-min);
	}

	static bool toss() {
		return roll(0, 1) == 1;
	}
	
	static float randF() {
		return 1.0f * rand() / RAND_MAX;
	}

	static float angleRad() {
		return randF() * 2 * (float)M_PI;
	}

	static float angleDeg() {
		return randF() * 360;
	}
};