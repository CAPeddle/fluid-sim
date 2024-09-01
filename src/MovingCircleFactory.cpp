#include "MovingCircleFactory.hpp"

#include <cstdlib>
#include <ctime>
MovingCircleFactory::MovingCircleFactory(const sf::Vector2u &windowSize, const EnvironmentProperties &environment)
    : m_windowSize(windowSize), m_environment(environment)
{
    std::srand(std::time(nullptr));
}

MovingCircle MovingCircleFactory::createDefault()
{
    ParticleProperties defaultParticle{
        sf::Vector2f(0.f, 0.f), sf::Vector2f(m_windowSize.x / 2.f, m_windowSize.y / 2.f), 50.f};
    return MovingCircle(m_windowSize, m_environment, defaultParticle);
}

MovingCircle MovingCircleFactory::createCustom(const ParticleProperties &particle)
{
    return MovingCircle(m_windowSize, m_environment, particle);
}

MovingCircle MovingCircleFactory::createRandom()
{
    float radius = static_cast<float>(rand() % 80 + 10);

    sf::Vector2f position{static_cast<float>(rand() % static_cast<int>(m_windowSize.x - radius) + radius),
                          static_cast<float>(rand() % static_cast<int>(m_windowSize.y - radius) + radius)};

    sf::Vector2f velocity{static_cast<float>(rand() % 100 - 50), static_cast<float>(rand() % 100 - 50)};

    ParticleProperties randomParticle{velocity, position, radius};
    return MovingCircle(m_windowSize, m_environment, randomParticle);
}
