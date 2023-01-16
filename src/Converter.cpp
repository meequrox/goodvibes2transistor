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

void Converter::buildConfigJSON() {
    // Modification date must be in the format "12/24/22 12:55 AM"
    configJSON["modificationDate"] = getCurrentDate();
    configJSON["stations"];
    configJSON["version"] = 0;

    size_t i = 0;
    for (const auto& station : configReader.getStationsList()) {
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
        stationJSON["modificationDate"] = configJSON["modificationDate"];
        stationJSON["name"] = station.first;
        stationJSON["streamUris"][0] = station.second;
        stationJSON["uuid"] = generateUUID();

        configJSON["stations"][i] = stationJSON;
        i++;
    }
}

void Converter::buildConfigM3U() {
    configM3U = "#EXTM3U\n\n";

    size_t i = 0;
    for (const auto& station : configReader.getStationsList()) {
        if (i) configM3U += "\n\n";

        configM3U += "#EXTINF:-1," + station.first + "\n";
        configM3U += station.second;

        i++;
    }
}

Converter::Converter(const ConfigReader& _configReader)
    : configReader(_configReader), configJSON(nullptr) {
    buildConfigJSON();
    buildConfigM3U();
}

static void createCollectionDir() {
    std::string sep(1, fs::path::preferred_separator);
    std::string path = fs::current_path().generic_string() + sep + "transistor_backup";
    fs::create_directory(path);

    path += sep + "collection";
    fs::create_directory(path);
}

void Converter::dumpJSON(bool verbose) const {
    if (verbose) {
        std::cout << std::endl << "JSON:" << std::endl << configJSON.dump(4) << std::endl;
    }

    std::string sep(1, fs::path::preferred_separator);
    std::string path = fs::current_path().generic_string() + sep + "transistor_backup" + sep +
                       "collection" + sep + "collection.json";

    std::ofstream file(path);

    if (!file) {
        std::cout << "Can't create json dump file: " << path << std::endl;
        return;
    }

    file << configJSON.dump();

    std::cout << "json is dumped to " << path << std::endl;
}

void Converter::dumpM3U(bool verbose) const {
    if (verbose) {
        std::cout << std::endl << "M3U:" << std::endl << configM3U << std::endl;
    }

    std::string sep(1, fs::path::preferred_separator);
    std::string path = fs::current_path().generic_string() + sep + "transistor_backup" + sep +
                       "collection" + sep + "collection.m3u";

    std::ofstream file(path);

    if (!file) {
        std::cout << "Can't create m3u dump file: " << path << std::endl;
        return;
    }

    file << configM3U << std::endl;

    std::cout << "m3u is dumped to " << path << std::endl;
}

static void dumpNomedia() {
    std::string sep(1, fs::path::preferred_separator);
    std::string path =
        fs::current_path().generic_string() + sep + "transistor_backup" + sep + ".nomedia";

    std::ofstream file(path);

    if (!file) {
        std::cout << "Can't create nomedia file: " << path << std::endl;
        return;
    }

    file << std::string(1, '\x00');
}

void Converter::dumpCollection(bool archive, bool verbose) const {
    createCollectionDir();

    dumpJSON(verbose);
    dumpM3U(verbose);
    dumpNomedia();
}
