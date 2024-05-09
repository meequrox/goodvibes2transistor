#pragma once

#include <string>
#include <vector>

namespace r2t {
using Station = std::pair<std::string, std::string>;
using Stations = std::vector<Station>;

namespace reader {
class Reader {
   public:
    /* Returns vector with pairs:
     * pair.first is station name
     * pair.second is station URI */
    virtual Stations read() const = 0;

    virtual ~Reader() = default;
};
}  // namespace reader
}  // namespace r2t
