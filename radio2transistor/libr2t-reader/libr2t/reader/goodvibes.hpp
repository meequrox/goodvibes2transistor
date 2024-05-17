#pragma once

#include <tinyxml2.h>

#include <libr2t/reader/reader.hpp>
#include <string>

namespace r2t::reader {
class Goodvibes : public Reader {
   public:
    Goodvibes(const std::string& path);

    Stations read() const override;

   private:
    tinyxml2::XMLDocument doc_;
    const tinyxml2::XMLElement* stations_;
};
}  // namespace r2t::reader
