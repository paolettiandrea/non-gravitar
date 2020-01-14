target_sources(non_gravitar PRIVATE
        EnemyBase.cpp
        EnemyBase.hpp

        EnemyCannon.cpp
        EnemyCannon.hpp

        EnemyPart.cpp
        EnemyPart.hpp

        Trigger.hpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(head)