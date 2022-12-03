set_languages("cxx20")
add_rules("mode.debug", "mode.release")

set_optimize("fastest")
-- add_includedirs("/opt/libtorch/include", "/usr/local/include", "/usr/include")
-- add_linkdirs("/opt/libtorch/lib", "/usr/local/lib", "/usr/lib")
add_cxflags("-fno-strict-aliasing", "-DDEBUG")
-- add_ldflags("-fuse-ld=mold", "-lpthread", {force = true})

add_requires("opencv", {system = true})
add_requires("fmt", {system = true})
add_requires("DIP", {system = true})
add_requires("libtorch")
add_requires("open3d")

target("resume")
    set_kind("binary")
    add_files("src/resume.cpp")
    add_packages("opencv", "fmt")

target("dipper")
    set_kind("binary")
    add_files("src/dipper.cpp")
    add_packages("fmt", "DIP")

target("classify")
    set_kind("binary")
    add_files("src/classify.cpp")
    add_packages("fmt", "opencv", "libtorch")
