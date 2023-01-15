#include "Converter.hpp"

#include <iostream>

static std::string getCurrentDate() {
    time_t time = std::time(nullptr);
    char timeString[std::size("dd/mm/yy hh:mm am")];

    strftime(std::data(timeString), std::size(timeString), "%D %I:%M %p", localtime(&time));

    return std::string(timeString);
}

Converter::Converter(const ConfigReader& _configReader) : configReader(_configReader), jsonMap(nullptr) {
    // Modification date must be in the format "12/24/22 12:55 AM"
    jsonMap["modificationDate"] = getCurrentDate();
    jsonMap["stations"];
    jsonMap["version"] = 0;

    // TODO: create json station list from stationsList
}

void Converter::dumpJSON() const { std::cout << jsonMap.dump(4) << std::endl; }
