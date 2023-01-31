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

    /* Returns vector with pairs:
     * pair.first is station name
     * pair.second is station uri */
    stationsList getStationsList() const override;

    void printStations(bool verbose) const override;
};

#endif  // GOODVIBES_READER_HPP
