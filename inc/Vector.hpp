#ifndef VECTORDRAWABLE_HPP
#define VECTORDRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class VectorDrawable : public sf::Drawable
{
   public:
    VectorDrawable(const sf::Vector2f& start, const sf::Vector2f& end)
        : startPoint(start), endPoint(end)
    {
        update();
    }

    void setPoints(const sf::Vector2f& start, const sf::Vector2f& end)
    {
        startPoint = start;
        endPoint = end;
        update();
    }

   private:
    sf::Vector2f startPoint;
    sf::Vector2f endPoint;
    sf::VertexArray line;
    sf::VertexArray arrowhead;

    void update()
    {
        // Update the line
        line = sf::VertexArray(sf::Lines, 2);
        line[0].position = startPoint;
        line[0].color = sf::Color::Red;
        line[1].position = endPoint;
        line[1].color = sf::Color::Red;

        // Calculate arrowhead points
        float arrowLength = 10.0f;
        float arrowAngle = 30.0f * 3.14159f / 180.0f;  // Convert to radians

        sf::Vector2f direction = endPoint - startPoint;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f unitDirection = direction / length;

        sf::Vector2f arrowPoint1 = endPoint
                                   - arrowLength
                                         * (std::cos(arrowAngle) * unitDirection
                                            + std::sin(arrowAngle) * sf::Vector2f(-unitDirection.y, unitDirection.x));
        sf::Vector2f arrowPoint2 = endPoint
                                   - arrowLength
                                         * (std::cos(arrowAngle) * unitDirection
                                            - std::sin(arrowAngle) * sf::Vector2f(-unitDirection.y, unitDirection.x));

        // Update the arrowhead
        arrowhead = sf::VertexArray(sf::Lines, 4);
        arrowhead[0].position = endPoint;
        arrowhead[0].color = sf::Color::Red;
        arrowhead[1].position = arrowPoint1;
        arrowhead[1].color = sf::Color::Red;
        arrowhead[2].position = endPoint;
        arrowhead[2].color = sf::Color::Red;
        arrowhead[3].position = arrowPoint2;
        arrowhead[3].color = sf::Color::Red;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(line, states);
        target.draw(arrowhead, states);
    }
};

#endif  // VECTORDRAWABLE_HPP