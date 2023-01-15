#include "Converter.hpp"

#include <uuid.h>

#include <iostream>

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

Converter::Converter(const ConfigReader& _configReader)
    : configReader(_configReader), configJSON(nullptr) {
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

void Converter::dumpJSON() const { std::cout << configJSON.dump(4) << std::endl; }
