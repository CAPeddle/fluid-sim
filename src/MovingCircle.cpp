
#include "MovingCircle.hpp"

#include <cmath>

MovingCircle::MovingCircle(const sf::Vector2u &windowSize,
                           const EnvironmentProperties &environment,
                           const ParticleProperties &particle)
    : sf::CircleShape(particle.radius),
      windowSize(windowSize),
      m_environment(environment),
      m_particleProperties(particle)
{
    setOrigin(particle.radius, particle.radius);
    setFillColor(sf::Color::Green);
    setPosition(particle.position);
}

void MovingCircle::update(float deltaTime)
{
    sf::Vector2f currentPosition = getPosition();

    m_particleProperties.velocity += m_environment.gravity * deltaTime;
    currentPosition += m_particleProperties.velocity * deltaTime;

    if (currentPosition.x + getRadius() > windowSize.x)
    {
        m_particleProperties.velocity.x *= -1 * m_environment.damping;

        currentPosition.x = windowSize.x - m_particleProperties.radius;
    }
    if (currentPosition.x < getRadius())
    {
        m_particleProperties.velocity.x *= -1 * m_environment.damping;
    }

    if (currentPosition.y + getRadius() > windowSize.y)
    {
        m_particleProperties.velocity.y *= -1 * m_environment.damping;

        currentPosition.y = windowSize.y - m_particleProperties.radius;
    }
    if (currentPosition.y < getRadius())
    {
        m_particleProperties.velocity.y *= -1 * m_environment.damping;
    }

    setPosition(currentPosition);
}

float MovingCircle::influence(const sf::Vector2f &point) const
{
    sf::Vector2f center = getPosition() + sf::Vector2f(getRadius(), getRadius());
    float distance = std::sqrt(std::pow(center.x - point.x, 2) + std::pow(center.y - point.y, 2));
    float sigma = getRadius() * 2.0f;  // Spread of the influence
    return std::exp(-distance * distance / (2 * sigma * sigma));
}