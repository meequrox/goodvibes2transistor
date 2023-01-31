#include "RadiotrayReader.hpp"

#include <exception>
#include <fstream>
#include <iostream>

RadiotrayReader::RadiotrayReader(const std::string& path) noexcept(false) {
    if (path.substr(path.find_last_of(".")) != ".json")
        throw std::invalid_argument(path + " is not a JSON file.");

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::invalid_argument("Error opening " + path + " file. Does it exist?");
    }

    try {
        bookmarks = nlohmann::json::parse(file);
    } catch (nlohmann::json::parse_error& ex) {
        std::cerr << "Parse error at byte " << ex.byte << std::endl;
    }
}

RadiotrayReader::stationsList RadiotrayReader::getStationsList() const {
    stationsList v;

    for (const auto& group : bookmarks) {
        for (const auto& station : group["stations"]) {
            v.push_back(std::make_pair(station["name"], station["url"]));
        }
    }

    return v;
}
