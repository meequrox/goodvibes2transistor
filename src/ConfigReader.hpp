#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <tinyxml2.h>

#include <string>
#include <vector>

class ConfigReader {
   private:
    tinyxml2::XMLDocument doc;
    const tinyxml2::XMLElement* stations;

   public:
    ConfigReader(const std::string& path);

    typedef std::vector<std::pair<std::string, std::string>> stationsList;

    /* Returns vector with pairs:
     * pair.first is station name
     * pair.second is station uri */
    stationsList getStationsList() const;

    void printStations() const;
};

#endif  // CONFIG_READER_HPP
