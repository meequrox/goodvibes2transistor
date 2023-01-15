cmake_minimum_required(VERSION 3.5)

project(g2t LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(TinyXML2 REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

add_executable(g2t src/main.cpp)

target_sources(g2t PRIVATE
    # Headers
    src/ConfigReader.hpp

    # Sources
    src/ConfigReader.cpp
)

target_link_libraries(g2t tinyxml2::tinyxml2 CLI11::CLI11)

set_target_properties(g2t PROPERTIES LINK_FLAGS_RELEASE -s)

install(TARGETS g2t
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
