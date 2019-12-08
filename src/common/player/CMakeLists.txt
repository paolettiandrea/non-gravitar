target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE
        Player.cpp
        Player.hpp

        PlayerCannon.cpp
        PlayerCannon.hpp)


add_subdirectory(player_body)
