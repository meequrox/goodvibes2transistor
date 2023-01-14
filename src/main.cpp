#include <iostream>

#include "ConfigReader.hpp"

int main() {
    ConfigReader cr(std::string("/home/") + std::getenv("USER") +
                    "/.local/share/goodvibes/stations.xml");
    cr.printStations();

    return 0;
}
