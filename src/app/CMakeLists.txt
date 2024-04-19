set(target_name radio2transistor)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(${target_name} PRIVATE main.cpp)

target_include_directories(${target_name} PUBLIC
  ${PROJECT_SOURCE_DIR}/external/zipper
)

find_package(CLI11 CONFIG REQUIRED)

# cpp-zipper library (https://github.com/yhirose/cpp-zipper)
INCLUDE (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  PKG_CHECK_MODULES(ZIP minizip)
endif (PKG_CONFIG_FOUND)

# uuid.h library (https://man7.org/linux/man-pages/man3/uuid.3.html)
find_path(LIBUUID_INCLUDE_DIR uuid.h PATH_SUFFIXES uuid)
find_library(LIBUUID_LIBRARY libuuid.so)
include_directories(${LIBUUID_INCLUDE_DIR})

target_link_libraries(${target_name} PRIVATE
  reader
  converter
  CLI11::CLI11
  ${ZIP_LIBRARIES}
  ${LIBUUID_LIBRARY}
)

set_target_properties(${target_name} PROPERTIES
  LINK_FLAGS_RELEASE -s
)
