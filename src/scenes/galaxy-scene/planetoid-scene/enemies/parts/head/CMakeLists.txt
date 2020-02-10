target_sources(non_gravitar PRIVATE
        EnemyHead.hpp
        EnemyHead.cpp

        MultiShotEnemyHead.cpp
        MultiShotEnemyHead.hpp

        SniperEnemyHead.cpp
        SniperEnemyHead.hpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(sniper)