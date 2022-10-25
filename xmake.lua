set_languages("cxx20")
add_rules("mode.debug", "mode.release")

set_optimize("fastest")
add_includedirs("/usr/include", "/usr/local/include")
add_linkdirs("/usr/local/lib", "/usr/lib")
-- add_cxflags("-stdlib", "-fno-strict-aliasing")
-- add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})

add_requires("opencv", {system = true})
add_requires("fmt", {system = true})
add_requires("DIP", {system = true})

target("resume")
    set_kind("binary")
    add_files("src/resume.cpp")
    add_packages("opencv", "fmt")

target("dipper")
    set_kind("binary")
    add_files("src/dipper.cpp")
    add_packages("fmt", "DIP")