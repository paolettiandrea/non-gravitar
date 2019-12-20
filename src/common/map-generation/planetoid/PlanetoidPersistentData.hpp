#ifndef NON_GRAVITAR_PLANETOIDPERSISTENTDATA_HPP
#define NON_GRAVITAR_PLANETOIDPERSISTENTDATA_HPP

#include <SGE/Path.hpp>
#include <MarchingMap.hpp>
#include <MapGenerator.hpp>
#include <utility-classes/ColorPalette.hpp>
#include "MapGenInfo.hpp"

/*!
 * /brief Holds the data necessary for the assembly of a Planetoid
 */
class PlanetoidPersistentData {
public:
    explicit PlanetoidPersistentData(const MapGenInfo& map_gen_info);

    virtual ~PlanetoidPersistentData();

    MapGenInfo map_gen_info;

    const unsigned int size;

    MapGenerator map_generator;
    MarchingMap* main_fill_square_grid;
    MarchingMap* secondary_fill_square_grid;
};


#endif //NON_GRAVITAR_PLANETOIDPERSISTENTDATA_HPP
