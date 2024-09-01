#include "MovingCircle.hpp"

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
    }
    if (currentPosition.x < getRadius())
    {
        m_particleProperties.velocity.x *= -1 * m_environment.damping;
    }

    if (currentPosition.y + getRadius() > windowSize.y)
    {
        m_particleProperties.velocity.y *= -1 * m_environment.damping;
    }
    if (currentPosition.y < getRadius())
    {
        m_particleProperties.velocity.y *= -1 * m_environment.damping;
    }

    setPosition(currentPosition);
}
