set_version("1.0.1")

add_rules("mode.debug", "mode.release")

set_languages("cxx17")
set_warnings("all", "error")
set_optimize("fastest")

if is_os("windows") then
    -- Use MSVC toolchain by default
    -- https://visualstudio.microsoft.com/ru/visual-cpp-build-tools/
    add_defines("_CRT_SECURE_NO_WARNINGS")

    add_requires("tinyxml2")
    add_requires("minizip")
else
    add_requires("tinyxml2", {system = true})
    add_requires("minizip", {system = true})
end

-- Header-only
add_requires("cli11", "nlohmann_json", "uuid_v4")

includes("external")
includes("radio2transistor")
