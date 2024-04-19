set(target_name converter)

set(LIBRARY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/${target_name})

add_library(${target_name} STATIC
  ${LIBRARY_INCLUDE_DIR}/common.hpp
  common.cpp
)

target_include_directories(${target_name} PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

set(JSON_BuildTests OFF)
find_package(nlohmann_json 3.5.0 REQUIRED)

target_link_libraries(${target_name} PUBLIC
  nlohmann_json::nlohmann_json
)

include(CompileOptions)
set_compile_options(${target_name})