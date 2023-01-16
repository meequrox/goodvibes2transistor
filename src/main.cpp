#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Formatter.hpp>
#include <iostream>

#include "ConfigReader.hpp"
#include "Converter.hpp"

int main(int argc, char** argv) {
    CLI::App app{"goodvibes2transistor"};

    // std::string("/home/") + std::getenv("USER") + "/.local/share/goodvibes/stations.xml"
    std::string configPath;
    bool archive = false;
    bool verbose = false;

    // TODO: add --find option, which attempts to find the station.xml file and print its path
    app.add_option("-i", configPath, "stations.xml file path")->check(CLI::ExistingFile)->required();
    app.add_flag("-v,--verbose", verbose, "be verbose (stations + dumps)");
    app.add_flag("-a,--archive", archive, "archive collection to backup zip file");

    CLI11_PARSE(app, argc, argv);

    if (verbose) std::cout << app.config_to_str() << std::endl;

    try {
        ConfigReader cr(configPath);
        cr.printStations(verbose);

        Converter converter(cr);
        converter.dumpCollection(archive, verbose);

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << ", exitting..." << std::endl;
    }

    return 0;
}
