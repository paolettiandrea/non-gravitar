target_sources(non_gravitar PRIVATE
        CratePersistentData.hpp

        ImprovementCrate.hpp

        ExtraLifeCratePersistentData.hpp
        ExtraLifeCratePersistentData.cpp

        FuelCratePersistentData.hpp
        FuelCratePersistentData.cpp
        MaxStaminaCratePersistentData.hpp
        MaxFuelCratePersistentData.hpp
        )

target_include_directories(non_gravitar PRIVATE .)