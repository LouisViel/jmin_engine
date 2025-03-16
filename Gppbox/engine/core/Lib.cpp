#include "Lib.hpp"
#include <SFML/Graphics.hpp>

//in secs

double Lib::getTimeStamp() //retourne le temps actuel en seconde
{
	std::chrono::nanoseconds ns =
		duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
	return ns.count() / 1000000000.0;
}

sf::Color Lib::makeFromHSV(float _h, float _s, float _v)
{
	sf::Glsl::Vec3 RGB;
	double H = _h, S = _s, V = _v,
		P, Q, T,
		fract;

	(H == 360.) ? (H = 0.) : (H /= 60.);
	fract = H - floor(H);

	P = V * (1. - S);
	Q = V * (1. - S * fract);
	T = V * (1. - S * (1. - fract));

	if (0. <= H && H < 1.)
		RGB = sf::Glsl::Vec3((float)V, (float)T, (float)P);
	else if (1. <= H && H < 2.)
		RGB = sf::Glsl::Vec3((float)Q, (float)V, (float)P);
	else if (2. <= H && H < 3.)
		RGB = sf::Glsl::Vec3((float)P, (float)V, (float)T);
	else if (3. <= H && H < 4.)
		RGB = sf::Glsl::Vec3((float)P, (float)Q, (float)V);
	else if (4. <= H && H < 5.)
		RGB = sf::Glsl::Vec3((float)T, (float)P, (float)V);
	else if (5. <= H && H < 6.)
		RGB = sf::Glsl::Vec3((float)V, (float)P, (float)Q);
	else
		RGB = sf::Glsl::Vec3(0., 0., 0.);

	return sf::Color(
		sf::Uint8(RGB.x * 255.0),
		sf::Uint8(RGB.y * 255.0),
		sf::Uint8(RGB.z * 255.0)
	);
}
