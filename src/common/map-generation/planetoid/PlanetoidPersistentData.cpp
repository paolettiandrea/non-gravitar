#include <PlanetoidPopulator.hpp>
#include "PlanetoidPersistentData.hpp"


PlanetoidPersistentData::PlanetoidPersistentData(const MapGenInfo& map_gen_info) : size(map_gen_info.size), map_generator(map_gen_info) {
    this->map_gen_info = map_gen_info;

    main_fill_square_grid = new MarchingMap(map_generator.combined_mask, 0.5, true);
    secondary_fill_square_grid = new MarchingMap(map_generator.secondary_fill_mask, 0.5, true);

    PlanetoidPopulator planetoid_populator(map_gen_info, *main_fill_square_grid, map_generator.entrance_coords);
}

PlanetoidPersistentData::~PlanetoidPersistentData() {
    delete (main_fill_square_grid);
    delete (secondary_fill_square_grid);
}


