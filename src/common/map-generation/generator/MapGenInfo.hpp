#ifndef NON_GRAVITAR_MAPGENINFO_HPP
#define NON_GRAVITAR_MAPGENINFO_HPP


#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <utility-classes/ColorPalette.hpp>
#include "EnemyPersistentData.hpp"
#include "COLORS.hpp"

class MapGenInfo {
public:
    unsigned int size = 100;
    unsigned int min_cave_volume = 100;
    unsigned int min_filled_region_volume = 2;


    ColorPalette palette = ColorPalette(NG_COLORS_EASY_PLANETOID);

    std::vector<EnemyPersistentData*> enemies_build_data;
};


#endif //NON_GRAVITAR_MAPGENINFO_HPP
