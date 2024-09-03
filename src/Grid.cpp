#include "Grid.hpp"

Grid::Grid(sf::Vector2u windowSize, unsigned int gridSize)
    : gridSize(gridSize)
{
    gridDimensions.x = (windowSize.x + gridSize - 1) / gridSize;
    gridDimensions.y = (windowSize.y + gridSize - 1) / gridSize;
}

void Grid::assignCirclesToGrid(const std::vector<std::shared_ptr<MovingCircle>>& circles)
{
    gridMap.clear();

    for (const auto& circle : circles)
    {
        sf::Vector2f position = circle->getPosition();
        int x = static_cast<int>(position.x) / gridSize;
        int y = static_cast<int>(position.y) / gridSize;

        gridMap[x][y].push_back(circle);
    }
}

std::vector<std::shared_ptr<MovingCircle>> Grid::getCirclesInCellAndAdjacent(int x, int y) const
{
    std::vector<std::shared_ptr<MovingCircle>> result;

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int adjX = x + dx;
            int adjY = y + dy;

            if (gridMap.find(adjX) != gridMap.end() && gridMap.at(adjX).find(adjY) != gridMap.at(adjX).end())
            {
                const auto& cellCircles = gridMap.at(adjX).at(adjY);
                result.insert(result.end(), cellCircles.begin(), cellCircles.end());
            }
        }
    }

    return result;
}
