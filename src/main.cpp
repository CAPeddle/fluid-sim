#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SimProperties.hpp>
#include <Vector.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "BackgroundDisplay.hpp"
#include "ConfigReader.hpp"
#include "EventHandler.hpp"
#include "Grid.hpp"
#include "MovingCircle.hpp"
#include "MovingCircleFactory.hpp"

int main()
{
    auto config_reader = std::make_shared<ConfigReader>("resources/config.toml");

    auto resolution = config_reader->getResolution();
    // todo: add error handling for sfml window
    sf::RenderWindow window(sf::VideoMode(resolution.first, resolution.second), "C++ Fluid Simulation");

    // EnvironmentProperties the_environment(std::make_shared<ConfigReader>(configReader));

    auto the_environment = std::make_shared<EnvironmentProperties>(config_reader);
    // clang-format off
    ParticleProperties particle_properties = {
        .radius = 5.f
        };
    // clang-format on

    MovingCircleFactory circle_factory(window.getSize(), the_environment);

    std::vector<MovingCircle> circles;
    // circles = circle_factory.createBox(5, 5, particle_properties);

    circles = circle_factory.fillRandom(19, particle_properties);
    Grid grid(window.getSize(), 10);

    // Create a VectorDrawable object

    sf::Clock clock;
    EventHandler eventHandler(the_environment);
    while (window.isOpen())
    {
        sf::Event event;
        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            eventHandler.EventPoll(window, event);
        }
        window.clear(sf::Color::Black);
        /*  -----------  */

        for (auto& circle : circles)
        {
            circle.update(dt);
        }

        BackGroundDisplay::calculateDensityAndColorBackground(window, circles);

        for (auto& circle : circles)
        {
            window.draw(circle);
        }

        auto clickLocation = eventHandler.getMouseClickLocation(event);
        if (clickLocation)
        {
            sf::Vector2f end(100.f, 100.f);

            auto gradient = SimProperties::calculateDensityGradient(*clickLocation, circles);
            sf::Vector2f start(clickLocation->x, clickLocation->y);
            VectorDrawable vectorDrawable(start, gradient);
            window.draw(vectorDrawable);
        }

        // Draw the vector
        /*  -----------  */
        window.display();
    }

    return 0;
}
