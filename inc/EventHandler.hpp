#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

class EventHandler
{
   public:
    void EventPoll(sf::RenderWindow& window, const sf::Event& event)
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            int thing = 0;
            adjustVariableWithKeyPress(event.key, thing, -1);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                isMousePressed = true;
                std::cout << "the left button was pressed" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
            }
        }

        if (isMousePressed && event.type == sf::Event::MouseMoved)
        {
            std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
            std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                isMousePressed = false;
                std::cout << "the left button was released" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
            }
        }
    }

   private:
    bool isMousePressed = false;

    void adjustVariableWithKeyPress(const sf::Event::KeyEvent& key_event, int& variable, int stepSize)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            variable += stepSize;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (variable - stepSize > 0)
            {
                variable -= stepSize;
            }
        }
        std::cout << "Current grid size: " << variable << "\n";
    }
};

#endif