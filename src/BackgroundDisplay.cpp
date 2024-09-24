#include "BackgroundDisplay.hpp"

#include <Vector.hpp>
#include <cmath>
#include <iostream>

#include "SimProperties.hpp"

// Define m_display_gridSize
int m_display_gridSize = 10;  // or any appropriate value

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

void BackGroundDisplay::calculateDensityAndColorBackground(const std::vector<std::shared_ptr<MovingCircle>>& circles)
{
    std::vector<std::vector<std::vector<std::shared_ptr<MovingCircle>>>> circleGrid(
        m_numRows_display,
        std::vector<std::vector<std::shared_ptr<MovingCircle>>>(m_numCols_display));

    // Assign circles to grid cells
    for (const auto& circle : circles)
    {
        int col = static_cast<int>(circle->getPosition().x) / m_display_gridSize;
        int row = static_cast<int>(circle->getPosition().y) / m_display_gridSize;
        if (row >= 0 && row < m_numRows_display && col >= 0 && col < m_numCols_display)
        {
            circleGrid[row][col].push_back(circle);
        }
    }

    std::vector<std::vector<float>> densityGrid(m_numRows_display, std::vector<float>(m_numCols_display, 0.0f));
    std::vector<std::vector<float>> densityGridNew(m_numRows_display, std::vector<float>(m_numCols_display, 0.0f));

    float maxDensity = 0;
    // Calculate density with influence functions
    for (const auto& circle : circles)
    {
        for (int row = 0; row < m_numRows_display; ++row)
        {
            for (int col = 0; col < m_numCols_display; ++col)
            {
                const sf::Vector2f& precomputedCellCenter = m_cellCenters[row][col];

                float temp = circle->influence(precomputedCellCenter);
                densityGrid[row][col] += temp;
                maxDensity = std::max(maxDensity, densityGrid[row][col]);  // Update maxDensity with the total density
            }
        }
    }

    maxDensity = 0;
    for (int row = 0; row < m_numRows_display; ++row)
    {
        for (int col = 0; col < m_numCols_display; ++col)
        {
            const sf::Vector2f& precomputedCellCenter = m_cellCenters[row][col];

            // Determine which grid point the precomputed cell center falls into
            int cellCol = static_cast<int>(precomputedCellCenter.x) / m_region_gridSize;
            int cellRow = static_cast<int>(precomputedCellCenter.y) / m_region_gridSize;

            // Ensure the calculated cell indices are within bounds
            if (cellRow >= 0 && cellRow < m_numRows_display && cellCol >= 0 && cellCol < m_numCols_display)
            {
                for (int i = std::max(0, row - 1); i <= std::min(m_numRows_display - 1, row + 1); ++i)
                {
                    for (int j = std::max(0, col - 1); j <= std::min(m_numCols_display - 1, col + 1); ++j)
                    {
                        for (const auto& circle : circleGrid[i][j])
                        {
                            const sf::Vector2f& cellCenter = m_cellCenters[row][col];

                            float temp = circle->influence(cellCenter);
                            densityGridNew[row][col] += temp;
                            maxDensity = std::max(maxDensity,
                                                  densityGrid[row][col]);  // Update maxDensity with the total density
                        }
                    }
                }
            }
        }
    }

    // Color the background based on density
    for (int row = 0; row < m_numRows_display; ++row)
    {
        for (int col = 0; col < m_numCols_display; ++col)
        {
            float density = densityGridNew[row][col];

            // Scale the density to the 0-255 range based on maxDensity
            int intensity = maxDensity > 0 ? std::min(255, static_cast<int>((density / maxDensity) * 255)) : 0;

            sf::RectangleShape cell(sf::Vector2f(m_display_gridSize, m_display_gridSize));
            cell.setPosition(col * m_display_gridSize, row * m_display_gridSize);

            // Red color with intensity scaled by density
            cell.setFillColor(sf::Color(intensity, 0, 255 - intensity));  // Blue to Red gradient
            renderWindow_.draw(cell);
        }
    }

    if (1 == 2)
    {
        // Compare each element in densityGrid to densityGridNew
        for (int row = 0; row < m_numRows_display; ++row)
        {
            for (int col = 0; col < m_numCols_display; ++col)
            {
                if (densityGrid[row][col] != densityGridNew[row][col])
                {
                    std::cout << "Density mismatch at (" << row << ", " << col
                              << "): " << "densityGrid = " << densityGrid[row][col] << ", "
                              << "densityGridNew = " << densityGridNew[row][col] << std::endl;
                }

                if ((std::abs(densityGrid[row][col] - densityGridNew[row][col]) < 1e-6)
                    && (densityGrid[row][col] != 0 || densityGridNew[row][col] != 0))
                {
                    std::cout << "Density approx equal at (" << row << ", " << col
                              << "): " << "densityGrid = " << densityGrid[row][col] << ", "
                              << "densityGridNew = " << densityGridNew[row][col] << std::endl;
                }
            }
        }

        if (densityGrid == densityGridNew)
        {
            std::cout << "Density Grids are equal" << std::endl;
        }
        else
        {
            // std::cout << "Density Grids are not equal" << std::endl;
        }
    }
}

void BackGroundDisplay::calculateDensityAndDrawVectors(const std::vector<std::shared_ptr<MovingCircle>>& circles)
{
    // sf::Vector2u windowSize = renderWindow_.getSize();
    // const int influenceRange = static_cast<int>(2 * configReader_->getInfluenceRange());

    // Define a grid to hold vectors of shared pointers to MovingCircle
    std::vector<std::vector<std::vector<std::shared_ptr<MovingCircle>>>> circleGrid(
        m_numRows_display,
        std::vector<std::vector<std::shared_ptr<MovingCircle>>>(m_numCols_display));

    // Assign circles to grid cells
    for (const auto& circle : circles)
    {
        int col = static_cast<int>(circle->getPosition().x) / m_display_gridSize;
        int row = static_cast<int>(circle->getPosition().y) / m_display_gridSize;
        if (row >= 0 && row < m_numRows_display && col >= 0 && col < m_numCols_display)
        {
            circleGrid[row][col].push_back(circle);
        }
    }

    std::vector<std::vector<float>> densityGrid(m_numRows_display, std::vector<float>(m_numCols_display, 0.0f));

    float maxDensity = 0;
    for (int row = 0; row < m_numRows_display; ++row)
    {
        for (int col = 0; col < m_numCols_display; ++col)
        {
            const sf::Vector2f& precomputedCellCenter = m_cellCenters[row][col];

            // Determine which grid point the precomputed cell center falls into
            int cellCol = static_cast<int>(precomputedCellCenter.x) / m_region_gridSize;
            int cellRow = static_cast<int>(precomputedCellCenter.y) / m_region_gridSize;

            // Ensure the calculated cell indices are within bounds
            if (cellRow >= 0 && cellRow < m_numRows_display && cellCol >= 0 && cellCol < m_numCols_display)
            {
                for (int i = std::max(0, row - 1); i <= std::min(m_numRows_display - 1, row + 1); ++i)
                {
                    for (int j = std::max(0, col - 1); j <= std::min(m_numCols_display - 1, col + 1); ++j)
                    {
                        for (const auto& circle : circleGrid[i][j])
                        {
                            const sf::Vector2f& cellCenter = m_cellCenters[row][col];

                            auto gradient = SimProperties::calculateDensityGradient(cellCenter, circles);
                            VectorDrawable vectorDrawable(cellCenter, cellCenter + gradient);
                            renderWindow_.draw(vectorDrawable);

                            float temp = circle->influence(cellCenter);
                            densityGrid[row][col] += temp;
                            maxDensity = std::max(maxDensity,
                                                  densityGrid[row][col]);  // Update maxDensity with the total density
                        }
                    }
                }
            }
        }
    }

    // float maxDensity = 0;
    // // Calculate density with influence functions
    // for (const auto& circle : circles)
    // {
    //     for (int row = 0; row < m_numRows_display; ++row)
    //     {
    //         for (int col = 0; col < m_numCols_display; ++col)
    //         {
    //             const sf::Vector2f& cellCenter = m_cellCenters[row][col];

    //             auto gradient = SimProperties::calculateDensityGradient(cellCenter, circles);
    //             VectorDrawable vectorDrawable(cellCenter, cellCenter + gradient);
    //             renderWindow_.draw(vectorDrawable);

    //             float temp = circle->influence(cellCenter);
    //             densityGrid[row][col] += temp;
    //             maxDensity = std::max(maxDensity, densityGrid[row][col]);  // Update maxDensity with the total
    //             density
    //         }
    //     }
    // }
    // std::cout << "Max Density: " << maxDensity << std::endl;
}
