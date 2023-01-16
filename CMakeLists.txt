cmake_minimum_required(VERSION 3.5)

project(g2t LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(TinyXML2 REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

set(JSON_BuildTests OFF)
find_package(nlohmann_json 3.9.0 REQUIRED)

# uuid.h library
find_path(LIBUUID_INCLUDE_DIR uuid.h PATH_SUFFIXES uuid)
find_library(LIBUUID_LIBRARY libuuid.so)
include_directories(${LIBUUID_INCLUDE_DIR})

# cpp-zipper library (https://github.com/yhirose/cpp-zipper)
INCLUDE (FindPkgConfig)
if (PKG_CONFIG_FOUND)
    PKG_CHECK_MODULES(ZIP minizip)
endif (PKG_CONFIG_FOUND)

add_executable(g2t src/main.cpp)

target_sources(g2t PRIVATE
    # Headers
    src/ConfigReader.hpp
    src/Converter.hpp

    # Sources
    src/ConfigReader.cpp
    src/Converter.cpp
)

target_link_libraries(g2t PRIVATE tinyxml2::tinyxml2 CLI11::CLI11 nlohmann_json::nlohmann_json ${LIBUUID_LIBRARY} ${ZIP_LIBRARIES})

set_target_properties(g2t PROPERTIES LINK_FLAGS_RELEASE -s)

install(TARGETS g2t
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
