target_sources(non_gravitar PRIVATE
        Fragment.cpp
        Fragment.hpp

        FragmentInfo.hpp

        BreakTrigger.cpp
        BreakTrigger.hpp

        BreakHandler.cpp
        BreakHandler.hpp

        BreakGenerator.cpp
        BreakGenerator.hpp

        TriangleOverlap.cpp
        TriangleOverlap.hpp
        )

target_include_directories(non_gravitar PRIVATE .)