# this is the build file for project 
# it is autogenerated by the xmake build system.
# do not edit by hand.

# project
cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0091 NEW)
project(dipper LANGUAGES CXX C)

# target
add_executable(dipper "")
set_target_properties(dipper PROPERTIES OUTPUT_NAME "dipper")
set_target_properties(dipper PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/linux/x86_64/release")
target_include_directories(dipper PRIVATE
    /usr/include
    /usr/local/include
)
target_compile_options(dipper PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-m64>
    $<$<COMPILE_LANGUAGE:CXX>:-m64>
    $<$<COMPILE_LANGUAGE:C>:-DNDEBUG>
    $<$<COMPILE_LANGUAGE:CXX>:-DNDEBUG>
)
set_target_properties(dipper PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(dipper PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(dipper PRIVATE $<$<CONFIG:Release>:-Ox -fp:fast>)
else()
    target_compile_options(dipper PRIVATE -O3)
endif()
if(MSVC)
else()
    target_compile_options(dipper PRIVATE -fvisibility=hidden)
endif()
if(MSVC)
    set_property(TARGET dipper PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
target_link_libraries(dipper PRIVATE
    fmt
    DIP
)
target_link_directories(dipper PRIVATE
    /usr/local/lib
    /usr/lib
)
target_link_options(dipper PRIVATE
    -m64
)
target_sources(dipper PRIVATE
    src/dipper.cpp
)

# target
add_executable(resume "")
set_target_properties(resume PROPERTIES OUTPUT_NAME "resume")
set_target_properties(resume PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/linux/x86_64/release")
target_include_directories(resume PRIVATE
    /usr/include
    /usr/local/include
)
target_include_directories(resume PRIVATE
    /usr/include/opencv4
)
target_compile_options(resume PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-m64>
    $<$<COMPILE_LANGUAGE:CXX>:-m64>
    $<$<COMPILE_LANGUAGE:C>:-DNDEBUG>
    $<$<COMPILE_LANGUAGE:CXX>:-DNDEBUG>
)
set_target_properties(resume PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(resume PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(resume PRIVATE $<$<CONFIG:Release>:-Ox -fp:fast>)
else()
    target_compile_options(resume PRIVATE -O3)
endif()
if(MSVC)
else()
    target_compile_options(resume PRIVATE -fvisibility=hidden)
endif()
if(MSVC)
    set_property(TARGET resume PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
target_link_libraries(resume PRIVATE
    opencv_stitching
    opencv_aruco
    opencv_bgsegm
    opencv_bioinspired
    opencv_ccalib
    opencv_dnn_objdetect
    opencv_dnn_superres
    opencv_dpm
    opencv_highgui
    opencv_face
    opencv_freetype
    opencv_fuzzy
    opencv_hdf
    opencv_hfs
    opencv_img_hash
    opencv_line_descriptor
    opencv_quality
    opencv_reg
    opencv_rgbd
    opencv_saliency
    opencv_shape
    opencv_stereo
    opencv_structured_light
    opencv_phase_unwrapping
    opencv_superres
    opencv_optflow
    opencv_surface_matching
    opencv_tracking
    opencv_datasets
    opencv_text
    opencv_dnn
    opencv_plot
    opencv_ml
    opencv_videostab
    opencv_videoio
    opencv_viz
    opencv_ximgproc
    opencv_video
    opencv_xobjdetect
    opencv_objdetect
    opencv_calib3d
    opencv_imgcodecs
    opencv_features2d
    opencv_flann
    opencv_xphoto
    opencv_photo
    opencv_imgproc
    opencv_core
    fmt
)
target_link_directories(resume PRIVATE
    /usr/local/lib
    /usr/lib
)
target_link_options(resume PRIVATE
    -m64
)
target_sources(resume PRIVATE
    src/resume.cpp
)

