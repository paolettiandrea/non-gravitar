target_sources(non_gravitar PRIVATE
        PlanetoidSceneTransitionTrigger.cpp
        PlanetoidSceneTransitionTrigger.hpp

        SceneTransitionHandler.cpp
        SceneTransitionHandler.hpp

        SolarSystemTransitionHandler.cpp
        SolarSystemTransitionHandler.hpp

        PlanetoidTransitionHandler.cpp
        PlanetoidTransitionHandler.hpp

        CompletionPrompt.cpp
        CompletionPrompt.hpp
        )

target_include_directories(non_gravitar PRIVATE .)