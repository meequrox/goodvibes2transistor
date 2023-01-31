#ifndef BOOKMARKS_READER_HPP
#define BOOKMARKS_READER_HPP

#include <iostream>
#include <string>
#include <vector>

class BookmarksReader {
   public:
    typedef std::vector<std::pair<std::string, std::string>> stationsList;

    /* Returns vector with pairs:
     * pair.first is station name
     * pair.second is station uri */
    virtual stationsList getStationsList() const = 0;

    virtual void printStations(bool verbose) const {
        const stationsList stations = this->getStationsList();

        if (verbose) {
            std::cout << "Stations:" << std::endl;

            for (const auto& pair : stations)
                std::cout << pair.first << ": " << pair.second << std::endl;
        }

        std::cout << "Read " << stations.size() << " stations from bookmarks file" << std::endl;
    }

    virtual ~BookmarksReader() = default;
};

#endif  // BOOKMARKS_READER_HPP
