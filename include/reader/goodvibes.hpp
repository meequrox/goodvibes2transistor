#ifndef R2T_GOODVIBES_HPP
#define R2T_GOODVIBES_HPP

#include <tinyxml2.h>

#include <string>

#include "reader/reader.hpp"

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

#endif
