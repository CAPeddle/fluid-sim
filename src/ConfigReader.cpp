#include "ConfigReader.hpp"

#include <iostream>
#include <toml.hpp>
#include <utility>

ConfigReader::ConfigReader(const std::string& filePath)
    : m_filePath(filePath)
{
    try
    {
        m_root = toml::parse(m_filePath);
    }
    catch (const toml::syntax_error& e)
    {
        std::cerr << "Failed to parse TOML file: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Error: Missing required configuration: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::pair<unsigned int, unsigned int> ConfigReader::getResolution() const
{
    std::pair<unsigned int, unsigned int> resolution;
    resolution.first = m_root.at("simulation").at("resolution").at("width").as_integer();
    resolution.second = m_root.at("simulation").at("resolution").at("height").as_integer();

    return resolution;
}

std::pair<float, float> ConfigReader::getGravity() const
{
    std::pair<float, float> gravityVector;
    gravityVector.first = m_root.at("environment").at("gravity").at("x").as_floating();
    gravityVector.second = m_root.at("environment").at("gravity").at("y").as_floating();

    return gravityVector;
}

float ConfigReader::getInfluenceRange() const { return m_root.at("environment").at("influenceRange").as_floating(); }

std::string ConfigReader::getFontPath() const { return m_root.at("simulation").at("fontPath").as_string(); }