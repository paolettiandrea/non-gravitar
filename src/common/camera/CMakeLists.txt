target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE
        CameraControls.cpp
        CameraControls.hpp)

add_subdirectory(follow)