target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE
        Player.cpp
        Player.hpp

        PlayerCannon.cpp
        PlayerCannon.hpp

        TractorBeam.cpp
        TractorBeam.hpp

        PlayerPersistentData.hpp
        PlayerPersistentData.cpp)


add_subdirectory(player_body)
add_subdirectory(ui)
