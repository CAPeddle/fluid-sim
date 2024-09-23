#ifndef BACKGROUNDDISPLAY_HPP
#define BACKGROUNDDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "MovingCircle.hpp"

class GridSizeException : public std::runtime_error
{
   public:
    GridSizeException(const std::string& message)
        : std::runtime_error(message)
    {
    }
};

// TODO: This class is ugly, refactor it
class BackGroundDisplay
{
   public:
    BackGroundDisplay(std::shared_ptr<ConfigReader> configReader, sf::RenderWindow& renderWindow)
        : configReader_(configReader),
          renderWindow_(renderWindow),
          m_display_gridSize(0),
          m_region_gridSize(0),
          m_numRows_display(0),
          m_numCols_display(0),
          m_numRows_region(0),
          m_numCols_region(0)
    {
        const int desiredGridSize = configReader_->getGridSize();  // Size of each grid cell

        auto windowSize = renderWindow_.getSize();
        try
        {
            m_display_gridSize = findNearestGridSize(windowSize, desiredGridSize);
        }
        catch (const GridSizeException& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
        std::cout << "Display Grid Size: " << m_display_gridSize << std::endl;

        const int influenceRange = static_cast<int>(2 * configReader_->getInfluenceRange());

        try
        {
            m_region_gridSize = findNearestGridSize(windowSize, influenceRange);
        }
        catch (const GridSizeException& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
        std::cout << "Region Grid Size: " << m_region_gridSize << std::endl;

        m_numRows_display = windowSize.y / m_display_gridSize;
        m_numCols_display = windowSize.x / m_display_gridSize;

        m_numRows_region = windowSize.y / m_region_gridSize;
        m_numCols_region = windowSize.x / m_region_gridSize;

        // Precompute cell centers
        m_cellCenters.resize(m_numRows_display, std::vector<sf::Vector2f>(m_numCols_display));
        for (int row = 0; row < m_numRows_display; ++row)
        {
            for (int col = 0; col < m_numCols_display; ++col)
            {
                m_cellCenters[row][col] = sf::Vector2f(col * m_display_gridSize + m_display_gridSize / 2.0f,
                                                       row * m_display_gridSize + m_display_gridSize / 2.0f);
            }
        }
    }

    void calculateDensityAndColorBackground(sf::RenderWindow& window, const std::vector<MovingCircle>& circles);
    void calculateDensityAndDrawVectors(const std::vector<std::shared_ptr<MovingCircle>>& circles);

   private:
    std::shared_ptr<ConfigReader> configReader_;
    int m_display_gridSize;
    int m_region_gridSize;

    std::vector<std::vector<sf::Vector2f>> m_cellCenters;
    sf::RenderWindow& renderWindow_;

    int m_numRows_display;
    int m_numCols_display;

    int m_numRows_region;
    int m_numCols_region;

    int findNearestGridSize(sf::Vector2u windowSize, int desiredGridSize);
};

#endif  // BACKGROUNDDISPLAY_HPP