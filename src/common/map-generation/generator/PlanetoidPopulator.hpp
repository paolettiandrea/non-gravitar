#ifndef NON_GRAVITAR_PLANETOIDPOPULATOR_HPP
#define NON_GRAVITAR_PLANETOIDPOPULATOR_HPP

#include "MarchingMap.hpp"
#include "MapGenInfo.hpp"

class PlanetoidPopulator {
public:
    PlanetoidPopulator (const MapGenInfo& map_gen_info, const MarchingMap& planetoid_square_grid, sge::Vec2<int> starting_point);

    sge::Vec2<int> find_highest_edge_coord(NoiseMap& values_map, std::vector<sge::Vec2<int>>& edge_coords);

private:
    std::vector<sge::Vec2<int>> basic_enemies_coords;

    void spawn_enemies(float space_needed, std::vector<EnemyPersistentData*> enemies_data, NoiseMap& affinity_map, const NoiseMap& space_map , std::vector<sge::Vec2<int>>& edge_coords, const MarchingMap &planetoid_square_grid);
};


#endif //NON_GRAVITAR_PLANETOIDPOPULATOR_HPP
