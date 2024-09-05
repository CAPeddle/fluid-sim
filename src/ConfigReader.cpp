#include "ConfigReader.hpp"

#include <iostream>

ConfigReader::ConfigReader(const std::string& filePath)
    : filePath(filePath)
{
}

void ConfigReader::readConfig()
{
    try
    {
        config = YAML::LoadFile(filePath);
    }
    catch (const YAML::Exception& e)
    {
        std::cerr << "Error reading config file: " << e.what() << std::endl;
    }
}

template <typename T>
T ConfigReader::getValue(const std::string& key) const
{
    try
    {
        return config[key].as<T>();
    }
    catch (const YAML::Exception& e)
    {
        std::cerr << "Error getting value for key " << key << ": " << e.what() << std::endl;
        throw;
    }
}