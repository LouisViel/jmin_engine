#include "Bresenham.hpp"
#include "engine/Utils.hpp"
#include <cmath>

std::vector<sf::Vector2i> bresenhamLine(int x1, int y1, int x2, int y2)
{
    std::vector<sf::Vector2i> results = std::vector<sf::Vector2i>();
    bresenhamLine(x1, y1, x2, y2, results);
    return results;
}

void bresenhamLine(int x1, int y1, int x2, int y2, std::vector<sf::Vector2i>& results)
{
    int x = x1, y = y1;
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = Utils::sign(x2 - x1);
    int sy = Utils::sign(y2 - y1);
    int err = dx - dy;

    while (!(x == x2 && y == y2)) {

        // Add with start position
        //results.emplace_back(x, y);

        int e2 = err * 2;
        int prevX = x;
        int prevY = y;

        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }

        // Manage diagonal cases (prio vertical)
        if (x != prevX && y != prevY) {
            results.emplace_back(prevX, y); 
        }

        // Add without start position
        results.emplace_back(x, y);
    }

    //int dx = std::abs(x2 - x1);
    //int dy = -std::abs(y2 - y1);
    //int sx = (x1 < x2) ? 1 : -1;
    //int sy = (y1 < y2) ? 1 : -1;
    //int err = dx + dy;

    //while (true) {
    //    results.emplace_back(x1, y1); // Ajouter la case courante

    //    if (x1 == x2 && y1 == y2) break;

    //    int e2 = 2 * err;
    //    if (e2 >= dy) {
    //        err += dy;
    //        x1 += sx;
    //    }
    //    if (e2 <= dx) {
    //        err += dx;
    //        y1 += sy;
    //    }
    //}
}