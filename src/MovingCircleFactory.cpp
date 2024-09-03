#include "MovingCircleFactory.hpp"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

MovingCircleFactory::MovingCircleFactory(const sf::Vector2u &windowSize, const EnvironmentProperties &environment)
    : m_windowSize(windowSize), m_environment(environment)
{
    std::srand(std::time(nullptr));
}

MovingCircle MovingCircleFactory::createDefault()
{
    ParticleProperties defaultParticle{sf::Vector2f(0.f, 0.f),
                                       sf::Vector2f(m_windowSize.x / 2.f, m_windowSize.y / 2.f),
                                       50.f};
    return MovingCircle(m_windowSize, m_environment, defaultParticle);
}

MovingCircle MovingCircleFactory::createCustom(const ParticleProperties &particle)
{
    return MovingCircle(m_windowSize, m_environment, particle);
}

MovingCircle MovingCircleFactory::createRandom()
{
    float radius = static_cast<float>(rand() % 60 + 10);

    sf::Vector2f position{static_cast<float>(rand() % static_cast<int>(m_windowSize.x - radius) + radius),
                          static_cast<float>(rand() % static_cast<int>(m_windowSize.y - radius) + radius)};

    sf::Vector2f velocity{static_cast<float>(rand() % 100 - 50), static_cast<float>(rand() % 100 - 50)};

    ParticleProperties randomParticle{velocity, position, radius};
    return MovingCircle(m_windowSize, m_environment, randomParticle);
}

std::vector<MovingCircle> MovingCircleFactory::createBox(unsigned int particlesPerRow,
                                                         unsigned int particlesPerCol,
                                                         const ParticleProperties properties)
{
    std::vector<MovingCircle> circles;
    circles.reserve(particlesPerCol * particlesPerRow);

    auto spacing = 2 * properties.radius + (properties.radius * 0.2);

    for (size_t i = 0; i < particlesPerCol * particlesPerRow; i++)
    {
        ParticleProperties particle_properties(properties);
        particle_properties.position.x
            = (i % particlesPerRow - particlesPerRow / 2.f + 0.5) * spacing + (m_windowSize.x / 2);
        particle_properties.position.y
            = (i / particlesPerRow - particlesPerCol / 2.f + 0.5) * spacing + (m_windowSize.y / 2);

        circles.emplace_back(createCustom(particle_properties));
    }

    return circles;
}

std::vector<MovingCircle> MovingCircleFactory::fillRandom(unsigned int num_particles,
                                                          const ParticleProperties properties)
{
    std::vector<MovingCircle> circles;
    circles.reserve(num_particles);

    auto spacing = 2 * properties.radius + (properties.radius * 0.2);

    for (size_t i = 0; i < num_particles; i++)
    {
        ParticleProperties particle_properties(properties);

        sf::Vector2f position{
            static_cast<float>(rand() % static_cast<int>(m_windowSize.x - properties.radius) + properties.radius),
            static_cast<float>(rand() % static_cast<int>(m_windowSize.y - properties.radius) + properties.radius)};

        particle_properties.position = position;

        circles.emplace_back(createCustom(particle_properties));
    }

    return circles;
}
