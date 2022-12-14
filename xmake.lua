set_languages("cxx20")
add_rules("mode.debug", "mode.release")

set_optimize("fastest")
add_cxflags("-fno-strict-aliasing", "-DDEBUG")

add_requires("opencv", {system = true})
add_requires("fmt")

target("main")
    set_kind("binary")
    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    add_packages("fmt", "opencv")
