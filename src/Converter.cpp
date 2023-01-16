#include "Converter.hpp"

#include <uuid.h>

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

static std::string getCurrentDate() {
    time_t time = std::time(nullptr);
    char timeString[std::size("dd/mm/yy hh:mm am")];

    strftime(std::data(timeString), std::size(timeString), "%D %I:%M %p", localtime(&time));

    return std::string(timeString);
}

static std::string generateUUID() {
    uuid_t uuid;
    uuid_generate(uuid);

    char uuidStr[std::size("00011122-2333-4445-5566-777888999000")];
    uuid_unparse_lower(uuid, uuidStr);

    return std::string(uuidStr);
}

void buildConfigJSON(Converter& converter) {
    // Modification date must be in the format "12/24/22 12:55 AM"
    converter.configJSON["modificationDate"] = getCurrentDate();
    converter.configJSON["stations"];
    converter.configJSON["version"] = 0;

    size_t i = 0;
    for (const auto& station : converter.configReader.getStationsList()) {
        nlohmann::json stationJSON(nullptr);

        // Default values
        stationJSON["homepage"] = "";
        stationJSON["image"] =
            "android.resource://org.y20k.transistor/drawable/ic_default_station_image_24dp";
        stationJSON["imageColor"] = -1;
        stationJSON["imageManuallySet"] = false;
        stationJSON["nameManuallySet"] = true;
        stationJSON["playbackState"] = 1;
        stationJSON["radioBrowserChangeUuid"] = "";
        stationJSON["radioBrowserStationUuid"] = "";
        stationJSON["remoteImageLocation"] = "";
        stationJSON["remoteStationLocation"] = "";
        stationJSON["smallImage"] =
            "android.resource://org.y20k.transistor/drawable/ic_default_station_image_24dp";
        stationJSON["starred"] = false;
        stationJSON["stream"] = 0;
        stationJSON["streamContent"] = "audio/mpeg";

        // Station-specific values
        stationJSON["modificationDate"] = converter.configJSON["modificationDate"];
        stationJSON["name"] = station.first;
        stationJSON["streamUris"][0] = station.second;
        stationJSON["uuid"] = generateUUID();

        converter.configJSON["stations"][i] = stationJSON;
        i++;
    }
}

void buildConfigM3U(Converter& converter) {
    converter.configM3U = "#EXTM3U\n\n";

    size_t i = 0;
    for (const auto& station : converter.configReader.getStationsList()) {
        if (i) converter.configM3U += "\n\n";

        converter.configM3U += "#EXTINF:-1," + station.first + "\n";
        converter.configM3U += station.second;

        i++;
    }
}

Converter::Converter(const ConfigReader& _configReader)
    : configReader(_configReader), configJSON(nullptr) {
    buildConfigJSON(*this);
    buildConfigM3U(*this);
}

void Converter::dumpJSON(bool toFile) const {
    if (toFile) {
        std::string path = fs::current_path().generic_string();
        path.push_back(fs::path::preferred_separator);
        path += "collection";
        fs::create_directory(path);

        path.push_back(fs::path::preferred_separator);
        path += "collection.json";

        std::ofstream file(path);

        std::cout << "Dump json to " << path << std::endl;

        if (!file) {
            std::cout << "Can't create json dump file: " << path << std::endl;
            return;
        }

        file << configJSON.dump() << std::endl;
    } else {
        std::cout << "JSON:" << std::endl << configJSON.dump(4) << std::endl;
    }
}

void Converter::dumpM3U(bool toFile) const {
    if (toFile) {
        std::string path = fs::current_path().generic_string();
        path.push_back(fs::path::preferred_separator);
        path += "collection";
        fs::create_directory(path);

        path.push_back(fs::path::preferred_separator);
        path += "collection.m3u";

        std::ofstream file(path);

        std::cout << "Dump m3u to " << path << std::endl;

        if (!file) {
            std::cout << "Can't create m3u dump file: " << path << std::endl;
            return;
        }

        file << configM3U << std::endl;
    } else {
        std::cout << "M3U:" << std::endl << configM3U << std::endl;
    }
}
