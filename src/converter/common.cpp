#include "converter/common.hpp"

#include <array>
#include <ctime>
#include <nlohmann/json.hpp>
#include <string>
#include <uuid_v4.h>
#include <random>

#include "reader/reader.hpp"

namespace {
std::string date_now() {
    constexpr size_t size = std::size("dd/mm/yy hh:mm am");
    std::array<char, size> str{};

    const time_t time = std::time(nullptr);
    (void) strftime(str.data(), str.size(), "%D %I:%M %p", localtime(&time));

    return {str.data()};
}
}  // namespace

namespace r2t::converter {
Common::Common(const reader::Reader& reader) : reader_(reader), json_(nullptr) {
    build_json();
    build_m3u();
}

void Common::build_json() {
    UUIDv4::UUIDGenerator<std::mt19937_64> uuid_generator;
    const r2t::reader::Reader::Stations stations = reader_.read();

    json_["modificationDate"] = date_now();
    json_["version"] = 0;
    json_["stations"];
    
    for (size_t i = 0; i < stations.size(); ++i) {
        nlohmann::json station(nullptr);

        station["modificationDate"] = json_["modificationDate"];
        station["name"] = stations[i].first;
        station["streamUris"][0] = stations[i].second;
        station["uuid"] = uuid_generator.getUUID().bytes();

        // Default
        station["homepage"] = "";
        station["image"] = "";
        station["imageColor"] = -1;
        station["imageManuallySet"] = false;
        station["isPlaying"] = false;
        station["nameManuallySet"] = true;
        station["radioBrowserChangeUuid"] = "";
        station["radioBrowserStationUuid"] = "";
        station["remoteImageLocation"] = "";
        station["remoteStationLocation"] = "";
        station["smallImage"] = "";
        station["starred"] = false;
        station["stream"] = 0;
        station["streamContent"] = "audio/mpeg";

        json_["stations"][i] = station;
    }
}

void Common::build_m3u() {
    m3u_ = "#EXTM3U\n\n";

    size_t i = 0;
    for (const auto& station : reader_.read()) {
        if (i) {
            m3u_ += "\n\n";
        }

        m3u_ += "#EXTINF:-1," + station.first + "\n";
        m3u_ += station.second;

        i++;
    }
}

nlohmann::json Common::json() const {
    return json_;
}

std::string Common::m3u() const {
    return m3u_;
}
}  // namespace r2t::converter
