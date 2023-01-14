#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <tinyxml2.h>

#include <iostream>

using namespace tinyxml2;

class ConfigReader {
   private:
    XMLDocument doc;
    XMLElement* stations;

   public:
    ConfigReader(std::string path);

    void printStations();
};

#endif  // CONFIG_READER_HPP
