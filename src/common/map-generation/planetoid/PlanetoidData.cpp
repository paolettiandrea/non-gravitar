#include <PlanetoidPopulator.hpp>
#include "PlanetoidData.hpp"

#include "MapGenerator.hpp"

PlanetoidData::PlanetoidData(const MapGenInfo& map_gen_info) : size(map_gen_info.size)
                                                             , planetoid_raw_mask(map_gen_info.size, map_gen_info.size) {
    this->map_gen_info = map_gen_info;
    MapGenerator map_generator(map_gen_info);
    main_fill_square_grid = new MarchingMap(map_generator.combined_mask, 0.5, true);

    secondary_fill_square_grid = new MarchingMap(map_generator.secondary_fill_mask, 0.5, true);

    PlanetoidPopulator planetoid_populator(map_gen_info, *main_fill_square_grid, map_generator.entry_coords);


}
