#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "BackgroundDisplay.hpp"
#include "EventHandler.hpp"
#include "Grid.hpp"
#include "MovingCircle.hpp"
#include "MovingCircleFactory.hpp"

int main()
{
    std::vector<MovingCircle> circles;

    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML kinda works!");

    sf::Font font;
    if (!font.loadFromFile("resources/3230-font.ttf"))
    {
        std::cerr << "Error: Could not load font file!" << std::endl;
        return -1;
    }

    EnvironmentProperties the_environment = {.gravity = {0.f, 10.f}, .damping = {0.9}, .influenceRange = 2.};

    MovingCircleFactory circle_factory(window.getSize(), the_environment);

    ParticleProperties particle_properties = {.radius = 10.f};

    // circles = circle_factory.createBox(5, 5, particle_properties);

    circles = circle_factory.fillRandom(19, particle_properties);
    Grid grid(window.getSize(), 10);  // Grid size of 100x100 pixels

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
