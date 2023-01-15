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

ConfigReader::stationsList ConfigReader::getStationsList() {
    stationsList v;
    tinyxml2::XMLElement* station = stations->FirstChildElement("Station");

    while (station) {
        tinyxml2::XMLText* name = station->FirstChildElement("name")->FirstChild()->ToText();
        tinyxml2::XMLText* uri = station->FirstChildElement("uri")->FirstChild()->ToText();

        v.push_back(std::make_pair(name->Value(), uri->Value()));

        station = station->NextSiblingElement("Station");
    }

    return v;
}

void ConfigReader::printStations() {
    stationsList stations = this->getStationsList();

    for (const auto& pair : stations) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
