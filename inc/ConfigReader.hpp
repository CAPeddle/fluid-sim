#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <toml.hpp>

class ConfigReader
{
   public:
    // Constructor that takes the path to the YAML file
    ConfigReader(const std::string& filePath);

    std::pair<float, float> getGravity() const;

    int getGridSize() const;

    float getParticleRadius() const;

    float getInfluenceRange() const;

    std::string getFontPath() const;

    float getDamping() const;

    std::pair<unsigned int, unsigned int> getResolution() const;

   private:
    std::string m_filePath;
    toml::value m_root;
};

#endif  // CONFIG_READER_H