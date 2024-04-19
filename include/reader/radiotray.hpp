#ifndef R2T_RADIOTRAY_HPP
#define R2T_RADIOTRAY_HPP

#include <nlohmann/json.hpp>
#include <string>

#include "reader/reader.hpp"

namespace r2t::reader {
class Radiotray : public Reader {
   public:
    Radiotray(const std::string& path);

    Stations read() const override;

   private:
    nlohmann::json bookmarks_;
};
}  // namespace r2t::reader

#endif
