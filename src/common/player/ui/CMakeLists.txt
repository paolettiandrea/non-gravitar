target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE
        PlayerUI.cpp
        PlayerUI.hpp

        PlayerLivesIndicator.cpp
        PlayerLivesIndicator.hpp

        ScoreIndicator.cpp
        ScoreIndicator.hpp)