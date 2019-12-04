#ifndef NON_GRAVITAR_MAPGENINFO_HPP
#define NON_GRAVITAR_MAPGENINFO_HPP


#include <SFML/Graphics/Color.hpp>
#include <vector>
#include "EnemyBuildData.hpp"

class MapGenInfo {
public:
    unsigned int size = 100;
    unsigned int min_cave_volume = 100;
    unsigned int min_filled_region_volume = 2;

    sf::Color primary_color = sf::Color::White;
    sf::Color secondary_color = sf::Color::Green;

    std::vector<EnemyBuildData*> enemies_to_spawn;
};


#endif //NON_GRAVITAR_MAPGENINFO_HPP
