#ifndef RADIOTRAY_READER_HPP
#define RADIOTRAY_READER_HPP

#include <nlohmann/json.hpp>

#include "BookmarksReader.hpp"

class RadiotrayReader : public BookmarksReader {
   private:
    nlohmann::json bookmarks;

   public:
    RadiotrayReader(const std::string& path);

    /* Returns vector with pairs:
     * pair.first is station name
     * pair.second is station uri */
    stationsList getStationsList() const override;

    void printStations(bool verbose) const override;
};

#endif  // RADIOTRAY_READER_HPP
