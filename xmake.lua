add_rules("mode.debug", "mode.release")

set_languages("cxx17")
set_warnings("all", "error")
set_optimize("fastest")

add_requires("cli11", "nlohmann-json")
add_requires("tinyxml2", {system = true})
add_requires("minizip", {system = true})


target("converter")
    set_kind("static")
    add_files("src/converter/*.cpp")
    add_includedirs("include/", {public = true})

    add_packages("nlohmann-json")
    add_links("uuid")


target("reader")
    set_kind("static")
    add_files("src/reader/*.cpp")
    add_includedirs("include/", {public = true})

    add_packages("nlohmann-json", "tinyxml2")


target("zipper")
    set_kind("headeronly")
    add_headerfiles("external/zipper/*.h")
    add_includedirs("external/", {public = true})


target("radio2transistor")
    set_default(true)

    set_kind("binary")
    add_files("src/app/*.cpp")

    add_deps("converter", "reader", "zipper")
    add_packages("cli11", "nlohmann-json", "minizip")
