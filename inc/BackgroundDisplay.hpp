#ifndef BACKGROUNDDISPLAY_HPP
#define BACKGROUNDDISPLAY_HPP

#include <SFML/Graphics.hpp>

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
    BackGroundDisplay(std::shared_ptr<ConfigReader> configReader)
        : configReader_(configReader)
    {
    }

    void calculateDensityAndColorBackground(sf::RenderWindow& window, const std::vector<MovingCircle>& circles);
    void calculateDensityAndDrawVectors(sf::RenderWindow& window, const std::vector<MovingCircle>& circles);

   private:
    std::shared_ptr<ConfigReader> configReader_;
};

#endif  // BACKGROUNDDISPLAY_HPP