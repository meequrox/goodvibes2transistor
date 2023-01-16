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

    void dumpJSON() const;
    void dumpJSON(std::string path) const;

    void dumpM3U() const;
    void dumpM3U(std::string path) const;

    friend void buildConfigJSON(Converter& converter);
    friend void buildConfigM3U(Converter& converter);
};

#endif  // CONVERTER_HPP
