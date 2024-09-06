#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
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
    ConfigReader configReader("resources/config.toml");

    auto resolution = configReader.getResolution();
    // todo: add error handling for sfml window
    sf::RenderWindow window(sf::VideoMode(resolution.first, resolution.second), "C++ Fluid Simulation");

    EnvironmentProperties the_environment(std::make_shared<ConfigReader>(configReader));

    // clang-format off
    ParticleProperties particle_properties = {
        .radius = 5.f
        };
    // clang-format on

    MovingCircleFactory circle_factory(window.getSize(), std::make_shared<EnvironmentProperties>(the_environment));

    std::vector<MovingCircle> circles;
    circles = circle_factory.createBox(5, 5, particle_properties);

    // circles = circle_factory.fillRandom(19, particle_properties);
    Grid grid(window.getSize(), 10);

    sf::Clock clock;
    EventHandler eventHandler;
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

        /*  -----------  */
        window.display();
    }

    return 0;
}
