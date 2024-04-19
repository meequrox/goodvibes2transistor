#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Error.hpp>
#include <CLI/Formatter.hpp>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>

#include "converter/common.hpp"
#include "reader/goodvibes.hpp"
#include "reader/radiotray.hpp"
#include "reader/reader.hpp"
#include "zipper.h"

class App {
   public:
    App(int argc, char** argv) : app_("radio2transistor") {
        app_.add_option("-i", bookmarks_,
                        "bookmarks file path; use -g instead if you don't know its location")
            ->group("Input");
        app_.add_flag("-g", "print bookmarks files paths then exit")->group("Input");

        parse_args(argc, argv);
        set_mode();
    }

    void run() {
        if (status_ == FAILED || app_.get_option("-h")->count()) {
            return;
        }

        if (mode_ == GUESS) {
            const std::vector<std::string> modes = {"Goodvibes", "Radiotray-NG"};

            for (const auto& m : modes) {
                std::cout << m << ": " << find_bookmarks_path(m) << '\n';
            }
        } else if (!app_.get_option("-g")->count() && !app_.get_option("-i")->count()) {
            app_.exit(CLI::Error("", "Either the -i option or the -g flag must be provided."));
        } else if (std::filesystem::exists(bookmarks_)) {
            auto reader = get_reader(bookmarks_);

            const r2t::converter::Common converter(*reader);
            archive(converter.json(), converter.m3u());
        } else {
            std::cout << "File does not exist: " << bookmarks_ << '\n';
        }
    }

   private:
    enum status { SUCCESS, FAILED };

    enum modes { GOODVIBES, RADIOTRAY, GUESS };

    CLI::App app_;
    std::string bookmarks_;
    modes mode_{GUESS};
    status status_{FAILED};

    int parse_args(int argc, char** argv) {
        try {
            app_.parse(argc, argv);
            status_ = SUCCESS;

            return 0;
        } catch (const CLI::ParseError& e) {
            status_ = FAILED;

            return app_.exit(e);
        }
    }

    void set_mode() {
        const std::string filename = bookmarks_.substr(bookmarks_.find_last_of('/') + 1);
        if (app_.get_option("-g")->count()) {
            mode_ = GUESS;
        } else if (filename == "stations.xml") {
            mode_ = GOODVIBES;
        } else if (filename == "bookmarks.json") {
            mode_ = RADIOTRAY;
        }
    }

    std::string find_bookmarks_path(const std::string& program) {
        const std::string data_home = std::getenv("XDG_DATA_HOME")
                                          ? std::getenv("XDG_DATA_HOME")
                                          : (std::getenv("HOME") + std::string("/.local/share"));
        const std::string config_home = std::getenv("XDG_CONFIG_HOME")
                                            ? std::getenv("XDG_CONFIG_HOME")
                                            : (std::getenv("HOME") + std::string("/.config"));

        std::string path;

        if (program == "Goodvibes") {
            path += data_home + std::string("/goodvibes/stations.xml");
        } else if (program == "Radiotray-NG") {
            path += config_home + std::string("/radiotray-ng/bookmarks.json");
        } else {
            return "program is not supported";
        }

        return std::filesystem::is_regular_file(path) ? path : "not found";
    }

    std::shared_ptr<r2t::reader::Reader> get_reader(const std::string& config) {
        using namespace r2t::reader;

        std::shared_ptr<Reader> r = nullptr;

        if (mode_ == GOODVIBES) {
            r = std::make_shared<Goodvibes>(config);
        } else if (mode_ == RADIOTRAY) {
            r = std::make_shared<Radiotray>(config);
        }

        return r;
    }

    void archive(const nlohmann::json& json, const std::string& m3u) const {
        zipper::Zip zip("transistor-backup.zip");

        if (!zip.is_open()) {
            std::cout << "Can't create backup archive\n";
            return;
        }

        zip.add_dir("collection");
        zip.add_file("collection/collection.json", json.dump());
        zip.add_file("collection/collection.m3u", m3u + "\n");
        zip.add_file(".nomedia", std::string(1, '\x00'));
        zip.close();
    }
};

int main(int argc, char** argv) {
    App app(argc, argv);
    app.run();

    return EXIT_SUCCESS;
}
