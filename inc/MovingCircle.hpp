#ifndef MOVINGCIRCLE_HPP
#define MOVINGCIRCLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Environment.hpp"

struct ParticleProperties
{
    sf::Vector2f velocity{0.f, 0.f};
    sf::Vector2f position;
    float radius;
};

class MovingCircle : public sf::CircleShape
{
   public:
    MovingCircle(const sf::Vector2u &windowSize,
                 std::shared_ptr<EnvironmentProperties> environment,
                 const ParticleProperties &particle);

    // Update method to update the circle's position based on a float deltaTime
    void update(float deltaTime);

    float influence(const sf::Vector2f &point) const;

   private:
    sf::Vector2u windowSize;

    std::shared_ptr<EnvironmentProperties> m_environment;
    ParticleProperties m_particleProperties;
    sf::Vector2f gravity{0.f, 10.f};
};

#endif  // MOVINGCIRCLE_HPP
