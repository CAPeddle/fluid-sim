#include "BackgroundDisplay.hpp"

#include <cmath>
#include <iostream>

int findNearestGridSize(sf::Vector2u windowSize, int desiredGridSize)
{
    // Calculate the potential grid sizes for both dimensions
    int nearestX = std::round(static_cast<float>(windowSize.x) / desiredGridSize) * desiredGridSize;
    int nearestY = std::round(static_cast<float>(windowSize.y) / desiredGridSize) * desiredGridSize;

    // Check if we can create a grid that fits both dimensions
    if (windowSize.x % nearestX == 0 && windowSize.y % nearestY == 0)
    {
        return desiredGridSize;  // The desired grid size is valid
    }

    // Check if there is a common grid size that is a multiple of both dimensions
    for (int gridSize = desiredGridSize; gridSize > 0; --gridSize)
    {
        if (windowSize.x % gridSize == 0 && windowSize.y % gridSize == 0)
        {
            return gridSize;
        }
    }

    // If we cannot find a valid grid size, throw an exception
    throw GridSizeException(
        "It is not possible to create a grid size that is a multiple of both x and y dimensions of the window size.");
}

void BackGroundDisplay::calculateDensityAndColorBackground(sf::RenderWindow& window,
                                                           const std::vector<MovingCircle>& circles)
{
    sf::Vector2u windowSize = window.getSize();
    const int desiredGridSize = 10;  // Size of each grid cell
    const int numRows = windowSize.y / desiredGridSize;
    const int numCols = windowSize.x / desiredGridSize;

    static int gridSize = 0;
    if (gridSize == 0)
    {
        try
        {
            gridSize = findNearestGridSize(windowSize, desiredGridSize);
        }
        catch (const GridSizeException& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    std::vector<std::vector<float>> densityGrid(numRows, std::vector<float>(numCols, 0.0f));

    // Calculate density with influence functions
    for (const auto& circle : circles)
    {
        for (int row = 0; row < numRows; ++row)
        {
            for (int col = 0; col < numCols; ++col)
            {
                sf::Vector2f cellCenter(col * gridSize + gridSize / 2.0f, row * gridSize + gridSize / 2.0f);
                densityGrid[row][col] += circle.influence(cellCenter);
            }
        }
    }

    // Color the background based on density
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            float density = densityGrid[row][col];
            int intensity = std::min(255, static_cast<int>(density * 255));  // Adjust multiplier for desired effect
            sf::RectangleShape cell(sf::Vector2f(gridSize, gridSize));
            cell.setPosition(col * gridSize, row * gridSize);
            cell.setFillColor(sf::Color(intensity, 0, 255 - intensity));  // Blue to Red gradient
            window.draw(cell);
        }
    }
}
