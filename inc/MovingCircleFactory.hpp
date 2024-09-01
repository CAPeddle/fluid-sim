#ifndef MOVINGCIRCLEFACTORY_HPP
#define MOVINGCIRCLEFACTORY_HPP

#include <SFML/Graphics.hpp>

#include "MovingCircle.hpp"

class MovingCircleFactory
{
    EnvironmentProperties m_environment = {.gravity = {0.f, 10.f}, .damping = {0.9}};

   public:
    MovingCircleFactory(const EnvironmentProperties &environment);

    MovingCircle createDefault(const sf::Vector2u &windowSize);
    MovingCircle createCustom(const sf::Vector2u &windowSize, const ParticleProperties &particle);
    MovingCircle createRandom(const sf::Vector2u &windowSize);
};

#endif  // MOVINGCIRCLEFACTORY_HPP
