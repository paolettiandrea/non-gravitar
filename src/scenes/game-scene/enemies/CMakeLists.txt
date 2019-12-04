target_sources(non_gravitar PRIVATE
        Enemy.cpp
        Enemy.hpp

        BasicEnemy.cpp
        BasicEnemy.hpp

        BigEnemy.hpp
        BigEnemy.cpp

        parts/EnemyBase.cpp
        parts/EnemyBase.hpp

        parts/EnemyHead.cpp
        parts/EnemyHead.hpp

        parts/EnemyPart.cpp
        parts/EnemyPart.hpp

        parts/EnemyEye.cpp
        parts/EnemyEye.hpp

        parts/Trigger.cpp
        parts/Trigger.hpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(breakable)
