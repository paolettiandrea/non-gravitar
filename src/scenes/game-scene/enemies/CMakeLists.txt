target_sources(non_gravitar PRIVATE
        BasicEnemy.cpp
        BasicEnemy.hpp

        parts/EnemyBase.cpp
        parts/EnemyBase.hpp

        parts/EnemyHead.cpp
        parts/EnemyHead.hpp

        parts/EnemyPart.cpp
        parts/EnemyPart.hpp

        parts/EnemyCannon.cpp
        parts/EnemyCannon.hpp

        parts/Trigger.cpp
        parts/Trigger.hpp
        )

target_include_directories(non_gravitar PRIVATE .)