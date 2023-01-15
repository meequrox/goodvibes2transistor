#include "ConfigReader.hpp"

#include <exception>
#include <iostream>

#include "../include/mime-types/mime_mapper.hpp"

ConfigReader::ConfigReader(std::string path) noexcept(false) {
    if (mime_types::get_type(path) != "application/xml") {
        throw std::invalid_argument(path + " is not an XML file");
    }

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
