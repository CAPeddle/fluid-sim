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

    auto the_environment = std::make_shared<EnvironmentProperties>(config_reader);
    BackGroundDisplay background_display(config_reader);
    ParticleProperties particle_properties(config_reader);
    MovingCircleFactory circle_factory(window.getSize(), the_environment, config_reader);

    std::vector<std::shared_ptr<MovingCircle>> circles;
    // circles = circle_factory.createBox(5, 5, particle_properties);

    circles = circle_factory.fillRandom(5, particle_properties);
    Grid grid(window.getSize(), 10);

    // Create text object for FPS display
    // Load font
    sf::Font font;
    if (!font.loadFromFile(config_reader->getFontPath()))
    {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.f, 10.f);

    sf::Clock clock;
    EventHandler eventHandler(the_environment);
    while (window.isOpen())
    {
        sf::Event event;
        sf::Event happened;
        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            happened = eventHandler.EventPoll(window, event);
        }
        window.clear(sf::Color::Black);
        /*  -----------  */

        for (auto& circle : circles)
        {
            circle->update(dt);
        }

        // BackGroundDisplay::calculateDensityAndColorBackground(window, circles);

        for (auto& circle : circles)
        {
            window.draw(*circle);
        }

        background_display.calculateDensityAndDrawVectors(window, circles);

        if (happened.type == sf::Event::MouseButtonPressed)
        {
            auto clickLocation = eventHandler.getMouseClickLocation(happened);
            if (clickLocation)
            {
                auto gradient = SimProperties::calculateDensityGradient(*clickLocation, circles);
                std::cout << "Gradient: " << gradient.x << ", " << gradient.y << std::endl;
                sf::Vector2f start(clickLocation->x, clickLocation->y);
                VectorDrawable vectorDrawable(start, start + gradient);
                window.draw(vectorDrawable);
            }
        }

        // Calculate and display FPS
        float fps = 1.f / dt;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
        window.draw(fpsText);

        // Draw the vector
        /*  -----------  */
        window.display();
    }

    return 0;
}
