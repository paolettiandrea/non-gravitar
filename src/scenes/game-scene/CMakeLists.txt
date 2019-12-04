target_sources(non_gravitar PRIVATE
        EntryLogic.hpp
        EntryLogic.cpp)

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(planetoids)
add_subdirectory(enemies)
