target("r2t-converter")
    set_kind("static")
    add_files("libr2t/converter/*.cpp")
    add_headerfiles("libr2t/converter/*.hpp")

    add_deps("r2t-reader")
    add_packages("nlohmann_json", {public = true})
    add_packages("uuid_v4", {public = true})

    add_includedirs("$(projectdir)/radio2transistor/libr2t-converter", {public = true})
