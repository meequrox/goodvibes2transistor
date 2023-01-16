#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Formatter.hpp>
#include <iostream>

#include "ConfigReader.hpp"
#include "Converter.hpp"

int main(int argc, char** argv) {
    CLI::App app{"goodvibes2transistor"};

    std::string configPath;

    CLI::Option* oInput = app.add_option("-i,--input", configPath,
                                         "stations.xml file path\n"
                                         "use -g instead if you don't know its location")
                              ->group("Input")
                              ->check(CLI::ExistingFile);
    CLI::Option* fGuess = app.add_flag("-g,--guess",
                                       "program will find stations.xml file by itself\n"
                                       "don't use with -i flag")
                              ->group("Input")
                              ->excludes(oInput);

    CLI::Option* fArchive =
        app.add_flag("-a,--archive", "archive collection to backup zip file")->group("Output");
    CLI::Option* fVerbose =
        app.add_flag("-v,--verbose", "be verbose (stations + dumps)")->group("Output");

    CLI11_PARSE(app, argc, argv);

    if (!fGuess->count() && !oInput->count()) {
        app.exit(CLI::Error("", "Either the -i option or the -g flag must be provided."));
        return EXIT_FAILURE;
    }

    if (fVerbose->count()) std::cout << app.config_to_str() << std::endl;

    if (fGuess->count()) {
        configPath =
            std::string("/home/") + std::getenv("USER") + "/.local/share/goodvibes/stations.xml";
        std::cout << "Guess mode: config is probably at " << configPath << std::endl;
    }

    try {
        ConfigReader cr(configPath);
        cr.printStations(fVerbose->count());

        Converter converter(cr);
        converter.dumpCollection(fArchive->count(), fVerbose->count());

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
