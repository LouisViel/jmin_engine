#pragma once
#include <vector>
#include <cstdlib>
#include "SFML/System/Vector2.hpp"

//https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_Bresenham 

void bresenhamLine(int x1, int y1, int x2, int y2, std::vector<sf::Vector2i>& results);
std::vector<sf::Vector2i> bresenhamLine(int x1, int y1, int x2, int y2);