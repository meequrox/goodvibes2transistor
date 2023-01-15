#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <tinyxml2.h>

#include <string>

class ConfigReader {
   private:
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* stations;

   public:
    ConfigReader(std::string path);

    void printStations();
};

#endif  // CONFIG_READER_HPP
