#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

struct EnvironmentProperties
{
    sf::Vector2f gravity{0.f, 10.f};
    double damping{0.5};
    float influenceRange{2.f};
};

#endif