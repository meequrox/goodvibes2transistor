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
    ConfigReader() {
        std::string path =
            std::string("/home/") + std::getenv("USER") + "/.local/share/goodvibes/stations.xml";
        doc.LoadFile(path.c_str());
        stations = doc.FirstChildElement("Stations");
    }

    void print() {
        XMLElement* station = stations->FirstChildElement("Station");

        while (station) {
            XMLText* name = station->FirstChildElement("name")->FirstChild()->ToText();
            XMLText* uri = station->FirstChildElement("uri")->FirstChild()->ToText();

            std::cout << name->Value() << ": " << uri->Value() << std::endl;

            station = station->NextSiblingElement("Station");
        }
    }
};

#endif  // CONFIG_READER_HPP
