#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <yaml-cpp/yaml.h>

#include <string>

class ConfigReader
{
   public:
    // Constructor that takes the path to the YAML file
    ConfigReader(const std::string& filePath);

    // Method to read the configuration file
    void readConfig();

    template <typename T>
    T getValue(const std::string& key) const;

   private:
    std::string filePath;
    YAML::Node config;
};

#endif  // CONFIG_READER_H