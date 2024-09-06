#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Environment.hpp"

class EventHandler
{
   public:
    EventHandler(std::shared_ptr<EnvironmentProperties> environment)
        : m_environment(environment)
    {
    }

    void EventPoll(sf::RenderWindow& window, const sf::Event& event)
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Num0:
                    m_environment->gravity.x += 1;
                    std::cout << "Gravity x: " << m_environment->gravity.x << "\n";
                    break;
                case sf::Keyboard::Num1:
                    m_environment->gravity.x -= 1;
                    std::cout << "Gravity x: " << m_environment->gravity.x << "\n";
                    break;
                case sf::Keyboard::Num2:
                    m_environment->gravity.y -= 1;
                    std::cout << "Gravity y: " << m_environment->gravity.y << "\n";
                    break;
                case sf::Keyboard::Num3:
                    m_environment->gravity.y += 1;
                    std::cout << "Gravity y: " << m_environment->gravity.y << "\n";
                    break;
                case sf::Keyboard::Num4:
                    m_environment->influenceRange += 1;
                    std::cout << "influenceRange: " << m_environment->influenceRange << "\n";
                    break;
                case sf::Keyboard::Num5:
                    m_environment->influenceRange -= 1;
                    std::cout << "influenceRange: " << m_environment->influenceRange << "\n";
                    break;
                default:
                    break;
            }
            // int thing = 0;
            // adjustVariableWithKeyPress(event.key, thing, -1);
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

    std::shared_ptr<EnvironmentProperties> m_environment;

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
;

#endif