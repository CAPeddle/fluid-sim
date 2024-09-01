#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "MovingCircle.hpp"
#include "MovingCircleFactory.hpp"

int main()
{
    std::vector<MovingCircle> circles;
    circles.reserve(10);

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML kinda works!");

    sf::Font font;
    if (!font.loadFromFile("resources/3230-font.ttf"))
    {
        std::cerr << "Error: Could not load font file!" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello, SFML!");
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition(50.f, 50.f);

    EnvironmentProperties the_environment = {.gravity = {0.f, 10.f}, .damping = {0.9}};
    MovingCircleFactory circle_factory(the_environment);

    circles.emplace_back(circle_factory.createRandom(window.getSize()));
    circles.emplace_back(circle_factory.createRandom(window.getSize()));
    circles.emplace_back(circle_factory.createDefault(window.getSize()));

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        /*  -----------  */

        for (auto &circle : circles)
        {
            circle.update(dt);
        }

        for (auto &circle : circles)
        {
            window.draw(circle);
        }

        window.draw(text);

        /*  -----------  */
        window.display();
    }

    return 0;
}
