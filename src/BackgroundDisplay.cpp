#include "BackgroundDisplay.hpp"

#include <Vector.hpp>
#include <cmath>
#include <iostream>

#include "SimProperties.hpp"

int BackGroundDisplay::findNearestGridSize(sf::Vector2u windowSize, int desiredGridSize)
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
    for (int display_gridSize = desiredGridSize; display_gridSize > 0; --display_gridSize)
    {
        if (windowSize.x % display_gridSize == 0 && windowSize.y % display_gridSize == 0)
        {
            return display_gridSize;
        }
    }

    // TODO Change window size to fit the grid size

    //  If we cannot find a valid grid size, throw an exception
    throw GridSizeException(
        "It is not possible to create a grid size that is a multiple of both x and y dimensions of the window size.");
}

void BackGroundDisplay::calculateDensityAndColorBackground(sf::RenderWindow& window,
                                                           const std::vector<MovingCircle>& circles)
{
    sf::Vector2u windowSize = window.getSize();
    const int desiredGridSize = configReader_->getGridSize();  // Size of each grid cell
    const int numRows_display = windowSize.y / desiredGridSize;
    const int numCols_display = windowSize.x / desiredGridSize;

    static int display_gridSize = 0;
    if (display_gridSize == 0)
    {
        try
        {
            display_gridSize = findNearestGridSize(windowSize, desiredGridSize);
        }
        catch (const GridSizeException& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    std::vector<std::vector<float>> densityGrid(numRows_display, std::vector<float>(numCols_display, 0.0f));

    float maxDensity = 0;
    // Calculate density with influence functions
    for (const auto& circle : circles)
    {
        for (int row = 0; row < numRows_display; ++row)
        {
            for (int col = 0; col < numCols_display; ++col)
            {
                sf::Vector2f cellCenter(col * display_gridSize + display_gridSize / 2.0f,
                                        row * display_gridSize + display_gridSize / 2.0f);
                float temp = circle.influence(cellCenter);
                densityGrid[row][col] += temp;
                maxDensity = std::max(maxDensity, densityGrid[row][col]);  // Update maxDensity with the total density
            }
        }
    }

    // Color the background based on density
    for (int row = 0; row < numRows_display; ++row)
    {
        for (int col = 0; col < numCols_display; ++col)
        {
            float density = densityGrid[row][col];

            // Scale the density to the 0-255 range based on maxDensity
            int intensity = maxDensity > 0 ? std::min(255, static_cast<int>((density / maxDensity) * 255)) : 0;

            sf::RectangleShape cell(sf::Vector2f(display_gridSize, display_gridSize));
            cell.setPosition(col * display_gridSize, row * display_gridSize);

            // Red color with intensity scaled by density
            cell.setFillColor(sf::Color(intensity, 0, 255 - intensity));  // Blue to Red gradient
            window.draw(cell);
        }
    }
}

void BackGroundDisplay::calculateDensityAndDrawVectors(const std::vector<std::shared_ptr<MovingCircle>>& circles)
{
    sf::Vector2u windowSize = renderWindow_.getSize();
    const int desiredGridSize = configReader_->getGridSize();  // Size of each grid cell
    const int influenceRange = static_cast<int>(2 * configReader_->getInfluenceRange());

    const int numRows_display = windowSize.y / m_display_gridSize;
    const int numCols_display = windowSize.x / m_display_gridSize;

    static int region_gridSize = 0;
    if (region_gridSize == 0)
    {
        try
        {
            region_gridSize = findNearestGridSize(windowSize, influenceRange);
        }
        catch (const GridSizeException& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
        std::cout << "Region Grid Size: " << region_gridSize << std::endl;
    }
    const int numRows_region = windowSize.y / region_gridSize;
    const int numCols_region = windowSize.x / region_gridSize;

    std::vector<std::vector<float>> densityGrid(numRows_display, std::vector<float>(numCols_display, 0.0f));

    // Precompute cell centers
    std::vector<std::vector<sf::Vector2f>> cellCenters(numRows_display, std::vector<sf::Vector2f>(numCols_display));
    for (int row = 0; row < numRows_display; ++row)
    {
        for (int col = 0; col < numCols_display; ++col)
        {
            cellCenters[row][col] = sf::Vector2f(col * m_display_gridSize + m_display_gridSize / 2.0f,
                                                 row * m_display_gridSize + m_display_gridSize / 2.0f);
        }
    }

    // TODO Create simulation grids and populate them with circles

    float maxDensity = 0;
    // Calculate density with influence functions
    for (const auto& circle : circles)
    {
        for (int row = 0; row < numRows_display; ++row)
        {
            for (int col = 0; col < numCols_display; ++col)
            {
                const sf::Vector2f& cellCenter = cellCenters[row][col];

                auto gradient = SimProperties::calculateDensityGradient(cellCenter, circles);
                VectorDrawable vectorDrawable(cellCenter, cellCenter + gradient);
                renderWindow_.draw(vectorDrawable);

                float temp = circle->influence(cellCenter);
                densityGrid[row][col] += temp;
                maxDensity = std::max(maxDensity, densityGrid[row][col]);  // Update maxDensity with the total density
            }
        }
    }
    // std::cout << "Max Density: " << maxDensity << std::endl;
}
