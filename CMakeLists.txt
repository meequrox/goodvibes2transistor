cmake_minimum_required(VERSION 3.5)

project(g2t LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(g2t src/main.cpp)

target_sources(g2t PRIVATE
    # Headers
    src/config_reader.hpp

    # Sources
    src/config_reader.cpp
)

set_target_properties(g2t PROPERTIES LINK_FLAGS_RELEASE -s)

install(TARGETS g2t
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
