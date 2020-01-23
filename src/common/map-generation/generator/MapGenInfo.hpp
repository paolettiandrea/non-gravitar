#ifndef NON_GRAVITAR_MAPGENINFO_HPP
#define NON_GRAVITAR_MAPGENINFO_HPP


#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <utility-classes/ColorPalette.hpp>
#include "COLORS.hpp"
#include "game-scene/crates/data/CratePersistentData.hpp"
#include "EnemyBuildData.hpp"

class MapGenInfo {
public:
    unsigned int size = 100;
    unsigned int min_cave_volume = 100;
    unsigned int min_filled_region_volume = 2;
    float difficulty_factor = 1.0;


    ColorPalette palette = PLANETOID_EASY_PALETTE;

    std::vector<EnemyBuildData*> enemies_persistent_data_vec;
    std::vector<CratePersistentData*> crates_persistent_data_vec;
};


#endif //NON_GRAVITAR_MAPGENINFO_HPP
