#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <nlohmann/json.hpp>

class BookmarksReader;

class Converter {
   private:
    const BookmarksReader& bookmarksReader;
    nlohmann::json bookmarksJSON;
    std::string bookmarksM3U;

    void buildBookmarksJSON();
    void buildBookmarksM3U();

    void dumpJSON(bool verbose) const;
    void dumpM3U(bool verbose) const;

   public:
    Converter(const BookmarksReader& _bookmarksReader);

    void dumpCollection(bool archive, bool verbose) const;
};

#endif  // CONVERTER_HPP
