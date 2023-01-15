#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Formatter.hpp>
#include <iostream>

#include "ConfigReader.hpp"

int main(int argc, char** argv) {
    CLI::App app{"goodvibes2transistor"};

    // std::string("/home/") + std::getenv("USER") + "/.local/share/goodvibes/stations.xml"
    std::string configPath;

    // TODO: add --find option, which attempts to find the station.xml file and print its path
    app.add_option("-i", configPath, "stations.xml file path")->check(CLI::ExistingPath)->required();
    CLI11_PARSE(app, argc, argv);

    try {
        ConfigReader cr(configPath);
        cr.printStations();

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << ", exitting..." << std::endl;
    }

    return 0;
}
