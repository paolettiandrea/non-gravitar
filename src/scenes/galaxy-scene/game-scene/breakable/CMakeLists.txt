target_sources(non_gravitar PRIVATE
        Fragment.cpp
        Fragment.hpp

        FragmentInfo.hpp

        trigger/BreakTrigger.cpp
        trigger/BreakTrigger.hpp

        handler/BreakHandler.cpp
        handler/BreakHandler.hpp

        generator/BreakGenerator.cpp
        generator/BreakGenerator.hpp
        generator/FragmentedLayerGenerator.cpp
        generator/FragmentedLayerGenerator.hpp

        TriangleOverlap.cpp
        TriangleOverlap.hpp
        )

target_include_directories(non_gravitar PRIVATE .)
target_include_directories(non_gravitar PRIVATE ./generator)
target_include_directories(non_gravitar PRIVATE ./trigger)
target_include_directories(non_gravitar PRIVATE ./handler)