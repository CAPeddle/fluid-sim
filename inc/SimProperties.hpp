#include <SFML/Graphics.hpp>
#include <cmath>

#include "MovingCircle.hpp"

class SimProperties
{
   public:
    SimProperties(double radius)
        : m_radius(radius)
    {
    }

    static double calculateDensity(const sf::Vector2f& ref_point, const std::vector<MovingCircle>& circles)
    {
        float mass = 1;
        float density;
        for (const auto& circle : circles)
        {
            density += mass * circle.influence(ref_point);
        }

        return density;
    }

    static sf::Vector2f calculateDensityGradient(const sf::Vector2f& ref_point,
                                                 const std::vector<MovingCircle>& circles)
    {
        const float stepSize = 1;
        float deltaX
            = calculateDensity(ref_point + sf::Vector2f(stepSize, 0), circles) - calculateDensity(ref_point, circles);
        float deltaY
            = calculateDensity(ref_point + sf::Vector2f(0, stepSize), circles) - calculateDensity(ref_point, circles);

        return sf::Vector2f(deltaX, deltaY);
    }

   private:
    double m_radius;
};