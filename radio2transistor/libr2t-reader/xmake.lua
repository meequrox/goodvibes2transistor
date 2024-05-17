target("r2t-reader")
    set_kind("static")
    add_files("libr2t/reader/*.cpp")
    add_headerfiles("libr2t/reader/*.hpp")

    add_packages("nlohmann_json", {public = true})
    add_packages("tinyxml2", {public = true})

    add_includedirs("$(projectdir)/radio2transistor/libr2t-reader", {public = true})
