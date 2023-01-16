#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <nlohmann/json.hpp>

#include "ConfigReader.hpp"

class Converter {
   private:
    const ConfigReader& configReader;
    nlohmann::json configJSON;
    std::string configM3U;

    void buildConfigJSON();
    void buildConfigM3U();

    void dumpJSON(bool verbose) const;
    void dumpM3U(bool verbose) const;

   public:
    Converter(const ConfigReader& _configReader);

    void dumpCollection(bool archive, bool verbose) const;
};

#endif  // CONVERTER_HPP
