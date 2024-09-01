#ifndef MOVINGCIRCLEFACTORY_HPP
#define MOVINGCIRCLEFACTORY_HPP

#include <SFML/Graphics.hpp>

#include "MovingCircle.hpp"

class MovingCircleFactory
{
    EnvironmentProperties m_environment = {.gravity = {0.f, 10.f}, .damping = {0.9}};
    ParticleProperties m_default_particle = {.velocity{0.f, 0.f}, .radius{10}};
    const sf::Vector2u m_windowSize;

   public:
    MovingCircleFactory(const sf::Vector2u &windowSize, const EnvironmentProperties &environment);

    MovingCircle createDefault();
    MovingCircle createCustom(const ParticleProperties &particle);
    MovingCircle createRandom();
};

#endif  // MOVINGCIRCLEFACTORY_HPP
