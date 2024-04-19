#include "converter/common.hpp"

#include <uuid/uuid.h>

#include <array>
#include <ctime>
#include <nlohmann/json.hpp>
#include <string>

#include "reader/reader.hpp"

namespace {
std::string date_now() {
    constexpr size_t size = std::size("dd/mm/yy hh:mm am");
    std::array<char, size> str{};

    const time_t time = std::time(nullptr);
    (void) strftime(str.data(), str.size(), "%D %I:%M %p", localtime(&time));

    return {str.data()};
}

std::string uuid4() {
    constexpr size_t size = std::size("00011122-2333-4445-5566-777888999000");
    std::array<char, size> str{};

    uuid_t uuid;
    auto* uuid_p = static_cast<unsigned char*>(uuid);

    uuid_generate(uuid_p);
    uuid_unparse_lower(uuid_p, str.data());

    return {str.data()};
}
}  // namespace

namespace r2t::converter {
Common::Common(const reader::Reader& reader) : reader_(reader), json_(nullptr) {
    build_json();
    build_m3u();
}

void Common::build_json() {
    json_["modificationDate"] = date_now();
    json_["stations"];
    json_["version"] = 0;

    size_t i = 0;
    for (const auto& station : reader_.read()) {
        nlohmann::json json(nullptr);

        json["modificationDate"] = json_["modificationDate"];
        json["name"] = station.first;
        json["streamUris"][0] = station.second;
        json["uuid"] = uuid4();

        // Default
        json["homepage"] = "";
        json["image"] = "";
        json["imageColor"] = -1;
        json["imageManuallySet"] = false;
        json["isPlaying"] = false;
        json["nameManuallySet"] = true;
        json["radioBrowserChangeUuid"] = "";
        json["radioBrowserStationUuid"] = "";
        json["remoteImageLocation"] = "";
        json["remoteStationLocation"] = "";
        json["smallImage"] = "";
        json["starred"] = false;
        json["stream"] = 0;
        json["streamContent"] = "audio/mpeg";

        json_["stations"][i] = json;
        i++;
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
