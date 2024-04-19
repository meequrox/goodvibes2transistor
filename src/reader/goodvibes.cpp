#include "reader/goodvibes.hpp"

#include <tinyxml2.h>

#include <stdexcept>
#include <string>

namespace r2t::reader {
Goodvibes::Goodvibes(const std::string& path) noexcept(false) {
    if (path.substr(path.find_last_of('.')) != ".xml") {
        throw std::invalid_argument(path + ": not an XML file.");
    }

    doc_.LoadFile(path.c_str());

    if (doc_.Error()) {
        throw std::invalid_argument("Error parsing " + path + " file. Does it exist?");
    }

    stations_ = doc_.FirstChildElement("Stations");
}

Goodvibes::Stations Goodvibes::read() const {
    Stations v;
    const tinyxml2::XMLElement* station = stations_->FirstChildElement("Station");

    while (station) {
        const tinyxml2::XMLText* name = station->FirstChildElement("name")->FirstChild()->ToText();
        const tinyxml2::XMLText* uri = station->FirstChildElement("uri")->FirstChild()->ToText();

        v.emplace_back(name->Value(), uri->Value());

        station = station->NextSiblingElement("Station");
    }

    return v;
}
}  // namespace r2t::reader
