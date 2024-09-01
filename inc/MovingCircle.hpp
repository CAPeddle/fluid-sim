#ifndef MOVINGCIRCLE_HPP
#define MOVINGCIRCLE_HPP

#include <SFML/Graphics.hpp>

struct ParticleProperties
{
    sf::Vector2f velocity{0.f, 0.f};
    sf::Vector2f position;
    float radius;
};

struct EnvironmentProperties
{
    sf::Vector2f gravity{0.f, 10.f};
    double damping{0.5};
};

class MovingCircle : public sf::CircleShape
{
   public:
    MovingCircle(const sf::Vector2u &windowSize,
                 const EnvironmentProperties &environment,
                 const ParticleProperties &particle);

    // Update method to update the circle's position based on a float deltaTime
    void update(float deltaTime);

   private:
    sf::Vector2u windowSize;  // Store the dimensions of the render window

    EnvironmentProperties m_environment;
    ParticleProperties m_particleProperties;
    sf::Vector2f gravity{0.f, 10.f};
};

#endif  // MOVINGCIRCLE_HPP
