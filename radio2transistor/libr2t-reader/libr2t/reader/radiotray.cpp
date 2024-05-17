#include <fstream>
#include <iostream>
#include <libr2t/reader/radiotray.hpp>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace r2t::reader {
Radiotray::Radiotray(const std::string& path) noexcept(false) {
    if (path.substr(path.find_last_of('.')) != ".json") {
        throw std::invalid_argument(path + ": not a JSON file.");
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::invalid_argument("Error opening " + path + " file. Does it exist?");
    }

    try {
        bookmarks_ = nlohmann::json::parse(file);
    } catch (nlohmann::json::parse_error& ex) {
        std::cerr << "Parse error at byte " << ex.byte << '\n';
    }
}

Stations Radiotray::read() const {
    Stations v;

    for (const auto& group : bookmarks_) {
        for (const auto& station : group["stations"]) {
            v.emplace_back(station["name"], station["url"]);
        }
    }

    return v;
}
}  // namespace r2t::reader
