#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <nlohmann/json.hpp>

#include "ConfigReader.hpp"

class Converter {
   private:
    const ConfigReader& configReader;
    nlohmann::json configJSON;

   public:
    Converter(const ConfigReader& _configReader);

    void dumpJSON() const;
};

#endif  // CONVERTER_HPP
