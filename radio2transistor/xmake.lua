target("radio2transistor")
    set_kind("binary")
    add_files("app/*.cpp")
    -- add_headerfiles("app/*.hpp")

    add_deps("converter", "reader", "zipper")
    add_packages("cli11")
    add_packages("nlohmann_json")
    add_packages("minizip")

    set_default(true)


target("converter")
    set_kind("static")
    add_files("converter/*.cpp")
    add_headerfiles("converter/*.hpp")

    add_packages("nlohmann_json", {public = true})
    add_packages("uuid_v4", {public = true})

    add_includedirs("$(projectdir)/radio2transistor", {public = true})


target("reader")
    set_kind("static")
    add_files("reader/*.cpp")
    add_headerfiles("reader/*.hpp")

    add_packages("nlohmann_json", {public = true})
    add_packages("tinyxml2", {public = true})

    add_includedirs("$(projectdir)/radio2transistor", {public = true})
