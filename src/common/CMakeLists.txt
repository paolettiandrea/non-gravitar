target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE
        COLORS.hpp
        )


add_subdirectory(player)
add_subdirectory(camera)
add_subdirectory(noise-generation)
add_subdirectory(map-generation)
add_subdirectory(shooting)
add_subdirectory(utility-logic)
add_subdirectory(utility-classes)
add_subdirectory(animations)