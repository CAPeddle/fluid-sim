#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>


#include "MovingCircle.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML kinda works!");

    sf::Font font;
    if (!font.loadFromFile("resources/3230-font.ttf")) {
        std::cerr << "Error: Could not load font file!" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello, SFML!");
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition (50.f,50.f);

    EnvironmentProperties the_environement = {
        .gravity = {0.f, 10.f},
        .damping = {0.9}
    };

    ParticleProperties shape_properties = {
        .position = {50.f,50.f}
        , .radius = {10.f}
    };
    MovingCircle shape(window.getSize(),the_environement,shape_properties);
    shape.setFillColor(sf::Color::Green);
            
    ParticleProperties drop_properties = {
    .position = {50.f,50.f}
    , .radius = {10.f}
    };

    MovingCircle drop(window.getSize(), the_environement, drop_properties);
    
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

        shape.update(dt);
        drop.update(dt);

        window.draw(shape);
        window.draw(drop);
        window.draw(text);

        /*  -----------  */
        window.display();
    }

    return 0;
}
