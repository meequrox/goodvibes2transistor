#ifndef BOOKMARKS_READER_HPP
#define BOOKMARKS_READER_HPP

#include <string>
#include <vector>

class BookmarksReader {
   public:
    typedef std::vector<std::pair<std::string, std::string>> stationsList;

    /* Returns vector with pairs:
     * pair.first is station name
     * pair.second is station uri */
    virtual stationsList getStationsList() const = 0;

    virtual void printStations(bool verbose) const = 0;

    virtual ~BookmarksReader() = default;
};

#endif  // BOOKMARKS_READER_HPP
