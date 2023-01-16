#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <nlohmann/json.hpp>

#include "ConfigReader.hpp"

class Converter {
   private:
    const ConfigReader& configReader;
    nlohmann::json configJSON;
    std::string configM3U;

   public:
    Converter(const ConfigReader& _configReader);

    void dumpJSON(bool verbose) const;
    void dumpM3U(bool verbose) const;

    friend void buildConfigJSON(Converter& converter);
    friend void buildConfigM3U(Converter& converter);
};

#endif  // CONVERTER_HPP
