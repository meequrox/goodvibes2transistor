#pragma once

#include <nlohmann/json.hpp>
#include <reader/reader.hpp>
#include <string>

namespace r2t::reader {
class Radiotray : public Reader {
   public:
    Radiotray(const std::string& path);

    Stations read() const override;

   private:
    nlohmann::json bookmarks_;
};
}  // namespace r2t::reader
