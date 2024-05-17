target("radio2transistor")
    set_kind("binary")
    add_files("*.cpp")
    -- add_headerfiles("*.hpp")

    add_deps("r2t", "zipper")
    add_packages("cli11")
    add_packages("nlohmann_json")
    add_packages("minizip")

    set_default(true)
