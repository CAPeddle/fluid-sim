#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

#include "MovingCircle.hpp"

class Grid
{
   public:
    Grid(sf::Vector2u windowSize, unsigned int gridSize);

    void assignCirclesToGrid(const std::vector<std::shared_ptr<MovingCircle>>& circles);
    std::vector<std::shared_ptr<MovingCircle>> getCirclesInCellAndAdjacent(int x, int y) const;

   private:
    unsigned int gridSize;
    sf::Vector2u gridDimensions;
    std::unordered_map<int, std::unordered_map<int, std::vector<std::shared_ptr<MovingCircle>>>> gridMap;
};

#endif  // GRID_HPP
