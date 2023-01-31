#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Formatter.hpp>
#include <filesystem>
#include <iostream>

#include "Converter.hpp"
#include "GoodvibesReader.hpp"
#include "RadiotrayReader.hpp"

class App {
   private:
    enum status { success, failed };
    enum modes { goodvibes, radiotray_ng, guess };

    CLI::App app;
    std::string bookmarksPath;
    modes mode;
    status status;

    void setMode() {
        std::string filename = bookmarksPath.substr(bookmarksPath.find_last_of("/") + 1);
        if (app.get_option("-g")->count())
            mode = guess;
        else if (filename == "stations.xml")
            mode = goodvibes;
        else if (filename == "bookmarks.json")
            mode = radiotray_ng;
    }

    int parseArgs(int argc, char** argv) {
        try {
            app.parse(argc, argv);
            status = success;

            return 0;
        } catch (const CLI::ParseError& e) {
            status = failed;

            return app.exit(e);
        }
    }

    std::string findGoodvibesBookmarks() {
        std::string file;
        if (std::getenv("XDG_DATA_HOME"))
            file = std::getenv("XDG_DATA_HOME");
        else
            file = std::string("/home/") + std::getenv("USER") + "/.local/share";

        file += std::string("/goodvibes/stations.xml");

        return std::filesystem::exists(file) ? file : "not found";
    }

    std::string findRadiotrayBookmarks() {
        std::string file;

        if (std::getenv("XDG_CONFIG_HOME"))
            file = std::getenv("XDG_CONFIG_HOME");
        else
            file = std::string("/home/") + std::getenv("USER") + "/.config";

        file += std::string("/radiotray-ng/bookmarks.json");

        return std::filesystem::exists(file) ? file : "not found";
    }

    BookmarksReader* getReader(std::string configPath) {
        BookmarksReader* r = nullptr;

        if (mode == goodvibes)
            r = new GoodvibesReader(configPath);
        else if (mode == radiotray_ng) {
            r = new RadiotrayReader(configPath);
        }

        return r;
    }

   public:
    App(int argc, char** argv) : app("goodvibes2transistor") {
        app.add_option("-i", bookmarksPath,
                       "bookmarks file path; use -g instead if you don't know its location")
            ->group("Input");
        app.add_flag("-g", "program will print bookmarks files paths then exit")->group("Input");

        app.add_flag("-a", "archive collection to backup zip file")->group("Output");
        app.add_flag("-v", "be verbose (stations + dumps)")->group("Output");

        parseArgs(argc, argv);
        setMode();
    }

    void run() {
        if (status == failed || app.get_option("-h")->count()) return;

        bool verbose = app.get_option("-v")->count();

        if (verbose) std::cout << app.config_to_str() << std::endl;

        if (mode == guess) {
            std::cout << "Goodvibes: " << findGoodvibesBookmarks() << std::endl;
            std::cout << "Radiotray-NG: " << findRadiotrayBookmarks() << std::endl;
        } else if (!app.get_option("-g")->count() && !app.get_option("-i")->count()) {
            app.exit(CLI::Error("", "Either the -i option or the -g flag must be provided."));
        } else if (std::filesystem::exists(bookmarksPath)) {
            BookmarksReader* cr = getReader(bookmarksPath);
            cr->printStations(verbose);

            Converter converter(*cr);
            converter.dumpCollection(app.get_option("-a")->count(), verbose);

            delete cr;
        } else
            std::cout << "File does not exist: " << bookmarksPath << std::endl;
    }
};

int main(int argc, char** argv) {
    App app(argc, argv);
    app.run();

    return EXIT_SUCCESS;
}
