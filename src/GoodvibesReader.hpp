#ifndef GOODVIBES_READER_HPP
#define GOODVIBES_READER_HPP

#include <tinyxml2.h>

#include "BookmarksReader.hpp"

class GoodvibesReader : public BookmarksReader {
   private:
    tinyxml2::XMLDocument doc;
    const tinyxml2::XMLElement* stations;

   public:
    GoodvibesReader(const std::string& path);

    stationsList getStationsList() const override;
};

#endif  // GOODVIBES_READER_HPP
