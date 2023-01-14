#include "ConfigReader.hpp"

ConfigReader::ConfigReader(std::string path) {
    doc.LoadFile(path.c_str());
    stations = doc.FirstChildElement("Stations");
}

void ConfigReader::printStations() {
    XMLElement* station = stations->FirstChildElement("Station");

    while (station) {
        XMLText* name = station->FirstChildElement("name")->FirstChild()->ToText();
        XMLText* uri = station->FirstChildElement("uri")->FirstChild()->ToText();

        std::cout << name->Value() << ": " << uri->Value() << std::endl;

        station = station->NextSiblingElement("Station");
    }
}
