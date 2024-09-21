#include "BackgroundDisplay.hpp"

#include <Vector.hpp>
#include <cmath>
#include <iostream>

#include "SimProperties.hpp"

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
    const int desiredGridSize = configReader_->getGridSize();  // Size of each grid cell
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

    float maxDensity = 0;
    // Calculate density with influence functions
    for (const auto& circle : circles)
    {
        for (int row = 0; row < numRows; ++row)
        {
            for (int col = 0; col < numCols; ++col)
            {
                sf::Vector2f cellCenter(col * gridSize + gridSize / 2.0f, row * gridSize + gridSize / 2.0f);
                float temp = circle.influence(cellCenter);
                densityGrid[row][col] += temp;
                maxDensity = std::max(maxDensity, densityGrid[row][col]);  // Update maxDensity with the total density
            }
        }
    }

    // Color the background based on density
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            float density = densityGrid[row][col];

            // Scale the density to the 0-255 range based on maxDensity
            int intensity = maxDensity > 0 ? std::min(255, static_cast<int>((density / maxDensity) * 255)) : 0;

            sf::RectangleShape cell(sf::Vector2f(gridSize, gridSize));
            cell.setPosition(col * gridSize, row * gridSize);

            // Red color with intensity scaled by density
            cell.setFillColor(sf::Color(intensity, 0, 255 - intensity));  // Blue to Red gradient
            window.draw(cell);
        }
    }
}

void BackGroundDisplay::calculateDensityAndDrawVectors(sf::RenderWindow& window,
                                                       std::vector<std::shared_ptr<MovingCircle>> circles)
{
    sf::Vector2u windowSize = window.getSize();
    const int desiredGridSize = configReader_->getGridSize();  // Size of each grid cell

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
    const int numRows = windowSize.y / gridSize;
    const int numCols = windowSize.x / gridSize;

    std::vector<std::vector<float>> densityGrid(numRows, std::vector<float>(numCols, 0.0f));

    // Precompute cell centers
    std::vector<std::vector<sf::Vector2f>> cellCenters(numRows, std::vector<sf::Vector2f>(numCols));
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            cellCenters[row][col] = sf::Vector2f(col * gridSize + gridSize / 2.0f, row * gridSize + gridSize / 2.0f);
        }
    }

    float maxDensity = 0;
    // Calculate density with influence functions
    for (const auto& circle : circles)
    {
        for (int row = 0; row < numRows; ++row)
        {
            for (int col = 0; col < numCols; ++col)
            {
                const sf::Vector2f& cellCenter = cellCenters[row][col];

                auto gradient = SimProperties::calculateDensityGradient(cellCenter, circles);
                VectorDrawable vectorDrawable(cellCenter, cellCenter + gradient);
                window.draw(vectorDrawable);

                float temp = circle->influence(cellCenter);
                densityGrid[row][col] += temp;
                maxDensity = std::max(maxDensity, densityGrid[row][col]);  // Update maxDensity with the total density
            }
        }
    }
    std::cout << "Max Density: " << maxDensity << std::endl;
}
