target("zipper")
    set_kind("headeronly")
    add_headerfiles("zipper/zipper.h")
    
    add_includedirs("$(projectdir)/external", {public = true})
