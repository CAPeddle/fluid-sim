#ifndef MOVINGCIRCLEFACTORY_HPP
#define MOVINGCIRCLEFACTORY_HPP

#include <SFML/Graphics.hpp>

#include "ConfigReader.hpp"  // Include the header file that defines the 'Config' class
#include "MovingCircle.hpp"

class MovingCircleFactory
{
    std::shared_ptr<EnvironmentProperties> m_environment;

    ParticleProperties m_default_particle = {
        .velocity{0.f, 0.f},
        .radius{10}
    };
    const sf::Vector2u m_windowSize;

    std::shared_ptr<ConfigReader> m_config;

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
