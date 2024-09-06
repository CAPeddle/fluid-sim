#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "ConfigReader.hpp"

class EnvironmentProperties
{
   public:
    EnvironmentProperties(std::shared_ptr<ConfigReader> configReader)
        : configReader_(configReader)
    {
        auto gravity = configReader->getGravity();
        auto influenceRange = configReader->getInfluenceRange();

        gravity = {gravity.first, gravity.second};
        damping = 0.9;
        influenceRange = influenceRange;

        if (!m_font.loadFromFile(configReader->getFontPath()))
        {
            throw std::runtime_error("Failed to load font");
        }
    }

    sf::Vector2f gravity{0.f, 10.f};
    double damping{0.5};
    float influenceRange{20.f};

   private:
    std::shared_ptr<ConfigReader> configReader_;
    sf::Font m_font;
};

#endif