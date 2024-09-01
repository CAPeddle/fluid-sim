#include "MovingCircleFactory.hpp"

#include <cstdlib>
#include <ctime>
MovingCircleFactory::MovingCircleFactory(const EnvironmentProperties &environment) : m_environment(environment)
{
    std::srand(std::time(nullptr));
}

MovingCircle MovingCircleFactory::createDefault(const sf::Vector2u &windowSize)
{
    ParticleProperties defaultParticle{
        sf::Vector2f(0.f, 0.f), sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f), 50.f};
    return MovingCircle(windowSize, m_environment, defaultParticle);
}

MovingCircle MovingCircleFactory::createCustom(const sf::Vector2u &windowSize, const ParticleProperties &particle)
{
    return MovingCircle(windowSize, m_environment, particle);
}

MovingCircle MovingCircleFactory::createRandom(const sf::Vector2u &windowSize)
{
    float radius = static_cast<float>(rand() % 80 + 10);  // Random radius between 10 and 110

    // Ensure that the circle is fully within the window bounds
    sf::Vector2f position{static_cast<float>(rand() % static_cast<int>(windowSize.x - (2 * radius)) + radius),
                          static_cast<float>(rand() % static_cast<int>(windowSize.y - (2 * radius)) + radius)};

    // Random velocity components within a reasonable range
    sf::Vector2f velocity{
        static_cast<float>(rand() % 100 - 50),  // Random velocity between -50 and 50 on x-axis
        static_cast<float>(rand() % 100 - 50)   // Random velocity between -50 and 50 on y-axis
    };

    ParticleProperties randomParticle{velocity, position, radius};
    return MovingCircle(windowSize, m_environment, randomParticle);
}
