#ifndef RADIOTRAY_READER_HPP
#define RADIOTRAY_READER_HPP

#include <nlohmann/json.hpp>

#include "BookmarksReader.hpp"

class RadiotrayReader : public BookmarksReader {
   private:
    nlohmann::json bookmarks;

   public:
    RadiotrayReader(const std::string& path);

    stationsList getStationsList() const override;
};

#endif  // RADIOTRAY_READER_HPP
