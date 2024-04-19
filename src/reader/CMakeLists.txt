set(target_name reader)

set(LIBRARY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/${target_name})

add_library(${target_name} STATIC
  ${LIBRARY_INCLUDE_DIR}/reader.hpp
  ${LIBRARY_INCLUDE_DIR}/goodvibes.hpp
  ${LIBRARY_INCLUDE_DIR}/radiotray.hpp
  goodvibes.cpp
  radiotray.cpp
)

target_include_directories(${target_name} PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

set(JSON_BuildTests OFF)
find_package(nlohmann_json 3.5.0 REQUIRED)

find_package(TinyXML2 REQUIRED)

target_link_libraries(${target_name} PUBLIC
  tinyxml2::tinyxml2
  nlohmann_json::nlohmann_json
)

include(CompileOptions)
set_compile_options(${target_name})