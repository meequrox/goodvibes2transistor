#include "ConfigReader.hpp"

#include <iostream>

ConfigReader::ConfigReader(std::string path) {
    doc.LoadFile(path.c_str());
    stations = doc.FirstChildElement("Stations");
}

void ConfigReader::printStations() {
    tinyxml2::XMLElement* station = stations->FirstChildElement("Station");

    while (station) {
        tinyxml2::XMLText* name = station->FirstChildElement("name")->FirstChild()->ToText();
        tinyxml2::XMLText* uri = station->FirstChildElement("uri")->FirstChild()->ToText();

        std::cout << name->Value() << ": " << uri->Value() << std::endl;

        station = station->NextSiblingElement("Station");
    }
}
