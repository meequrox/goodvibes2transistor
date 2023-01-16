#include "ConfigReader.hpp"

#include <exception>
#include <iostream>

ConfigReader::ConfigReader(const std::string& path) noexcept(false) {
    if (path.substr(path.find_last_of(".")) != ".xml") {
        throw std::invalid_argument(path + " is not an XML file");
    }

    doc.LoadFile(path.c_str());
    stations = doc.FirstChildElement("Stations");
}

ConfigReader::stationsList ConfigReader::getStationsList() const {
    stationsList v;
    const tinyxml2::XMLElement* station = stations->FirstChildElement("Station");

    while (station) {
        const tinyxml2::XMLText* name = station->FirstChildElement("name")->FirstChild()->ToText();
        const tinyxml2::XMLText* uri = station->FirstChildElement("uri")->FirstChild()->ToText();

        v.push_back(std::make_pair(name->Value(), uri->Value()));

        station = station->NextSiblingElement("Station");
    }

    return v;
}

void ConfigReader::printStations(bool verbose) const {
    const stationsList stations = this->getStationsList();

    if (verbose) {
        std::cout << "Stations:" << std::endl;

        for (const auto& pair : stations) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    std::cout << "Read " << stations.size() << " stations from config" << std::endl;
}
