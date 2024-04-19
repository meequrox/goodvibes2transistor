#ifndef R2T_READER_HPP
#define R2T_READER_HPP

#include <string>
#include <vector>

namespace r2t::reader {
class Reader {
   public:
    using Station = std::pair<std::string, std::string>;
    using Stations = std::vector<Station>;

    /* Returns vector with pairs:
     * pair.first is station name
     * pair.second is station URI */
    virtual Stations read() const = 0;

    virtual ~Reader() = default;
};
}  // namespace r2t::reader

#endif
