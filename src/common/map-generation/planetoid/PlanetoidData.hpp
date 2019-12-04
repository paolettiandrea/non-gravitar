#ifndef NON_GRAVITAR_PLANETOIDDATA_HPP
#define NON_GRAVITAR_PLANETOIDDATA_HPP

#include <SGE/Path.hpp>
#include <MarchingMap.hpp>
#include "MapGenInfo.hpp"

/*!
 * /brief Holds the data necessary for the assembly of a Planetoid
 */
class PlanetoidData {
public:
    explicit PlanetoidData(const MapGenInfo& map_gen_info);

    MapGenInfo map_gen_info;

    const unsigned int size;
    // A list of closed paths tracing the walls of the planetoid
    std::vector<sge::Path> planetoid_walls;

    MarchingMap* main_fill_square_grid;
    MarchingMap* secondary_fill_square_grid;

    NoiseMap planetoid_raw_mask;
};


#endif //NON_GRAVITAR_PLANETOIDDATA_HPP
