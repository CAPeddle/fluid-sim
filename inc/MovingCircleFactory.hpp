#ifndef MOVINGCIRCLEFACTORY_HPP
#define MOVINGCIRCLEFACTORY_HPP

#include <SFML/Graphics.hpp>

#include "ConfigReader.hpp"
#include "MovingCircle.hpp"

class MovingCircleFactory
{
    ParticleProperties m_defaultParticle{
        sf::Vector2f(0.f, 0.f), sf::Vector2f(m_windowSize.x / 2.f, m_windowSize.y / 2.f), 50.f};

    const sf::Vector2u m_windowSize;
    std::shared_ptr<EnvironmentProperties> m_environment;

   public:
    MovingCircleFactory(const sf::Vector2u &windowSize, std::shared_ptr<EnvironmentProperties> environment);

    MovingCircle createDefault();
    MovingCircle createCustom(const ParticleProperties &particle);
    MovingCircle createRandom();

    std::vector<MovingCircle> createBox(unsigned int particlesPerRow,
                                        unsigned int particlesPerCol,
                                        const ParticleProperties properties);
    std::vector<MovingCircle> fillRandom(unsigned int num_particles, const ParticleProperties properties);
};

#endif  // MOVINGCIRCLEFACTORY_HPP
