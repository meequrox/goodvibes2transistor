target("radio2transistor")
    set_kind("binary")
    add_files("app/*.cpp")
    set_default(true)

    add_deps("converter", "reader", "zipper")
    add_packages("cli11", "nlohmann_json", "minizip")


target("converter")
    set_kind("static")
    add_files("converter/*.cpp")
    add_includedirs("$(projectdir)/radio2transistor", {public = true})

    add_packages("nlohmann_json", "uuid_v4")


target("reader")
    set_kind("static")
    add_files("reader/*.cpp")
    add_includedirs("$(projectdir)/radio2transistor", {public = true})

    add_packages("nlohmann_json", "tinyxml2")
