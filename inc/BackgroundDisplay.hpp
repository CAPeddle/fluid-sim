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
        : configReader_(configReader), renderWindow_(renderWindow)
    {
        const int desiredGridSize = configReader_->getGridSize();  // Size of each grid cell
        static int display_gridSize = 0;

        try
        {
            m_display_gridSize = findNearestGridSize(renderWindow_.getSize(), desiredGridSize);
        }
        catch (const GridSizeException& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
        std::cout << "Display Grid Size: " << m_display_gridSize << std::endl;
    }

    void calculateDensityAndColorBackground(sf::RenderWindow& window, const std::vector<MovingCircle>& circles);
    void calculateDensityAndDrawVectors(const std::vector<std::shared_ptr<MovingCircle>>& circles);

   private:
    std::shared_ptr<ConfigReader> configReader_;
    int m_display_gridSize = 0;

    sf::RenderWindow& renderWindow_;

    int findNearestGridSize(sf::Vector2u windowSize, int desiredGridSize);
};

#endif  // BACKGROUNDDISPLAY_HPP