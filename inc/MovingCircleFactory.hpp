#ifndef MOVINGCIRCLEFACTORY_HPP
#define MOVINGCIRCLEFACTORY_HPP

#include <SFML/Graphics.hpp>

#include "ConfigReader.hpp"
#include "MovingCircle.hpp"

class MovingCircleFactory
{
    const sf::Vector2u m_windowSize;
    std::shared_ptr<EnvironmentProperties> m_environment;
    std::shared_ptr<ConfigReader> m_configReader;

   public:
    MovingCircleFactory(const sf::Vector2u &windowSize,
                        std::shared_ptr<EnvironmentProperties> environment,
                        std::shared_ptr<ConfigReader> configReader);

    MovingCircle createCustom(const ParticleProperties &particle);
    MovingCircle createRandom();

    std::vector<std::shared_ptr<MovingCircle>> createBox(unsigned int particlesPerRow,
                                                         unsigned int particlesPerCol,
                                                         const ParticleProperties properties);
    std::vector<std::shared_ptr<MovingCircle>> fillRandom(unsigned int num_particles,
                                                          const ParticleProperties properties);
};

#endif  // MOVINGCIRCLEFACTORY_HPP
