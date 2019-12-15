#include "MiniaturePlanetoid.hpp"
#include <math.h>

MiniaturePlanetoid::MiniaturePlanetoid(PlanetoidPersistentData *data, float grid_size) {
    persistent_data = data;
    this->grid_size = grid_size;

    NoiseMap& flooded_map = persistent_data->map_generator.flooded_map;


    NoiseMap* scaled_noise_map = downscale_noisemap(data->map_generator.combined_mask, grid_size,data->map_generator.flooded_map);
    m_scaled_marching_map = new MarchingMap(*scaled_noise_map, 0.5, true);

    NoiseMap* scaled_secondary_noise_map = downscale_noisemap(data->map_generator.secondary_fill_mask, grid_size);
    m_scaled_secondary_marching_map = new MarchingMap(*scaled_secondary_noise_map, 0.5, true);

    delete (scaled_noise_map);
    delete (scaled_secondary_noise_map);
}

void MiniaturePlanetoid::on_start() {
    auto vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    Planetoid::assemble_vert_array(vert_array, *m_scaled_marching_map, persistent_data->map_gen_info.palette.primary);
    Planetoid::assemble_vert_array(vert_array, *m_scaled_secondary_marching_map, persistent_data->map_gen_info.palette.dark);

}

MiniaturePlanetoid::~MiniaturePlanetoid() {
    delete (m_scaled_marching_map);
    delete (m_scaled_secondary_marching_map);
}

MiniaturePlanetoid::MiniaturePlanetoid(MiniaturePlanetoid *base) {
    grid_size = base->grid_size;
    m_scaled_marching_map = base->m_scaled_marching_map;
    m_scaled_secondary_marching_map = base->m_scaled_secondary_marching_map;
    persistent_data = base->persistent_data;
}

MarchingMap *MiniaturePlanetoid::get_scaled_marching_map() const {
    return m_scaled_marching_map;
}

NoiseMap* MiniaturePlanetoid::downscale_noisemap(const NoiseMap &in, float grid_size, const NoiseMap &flood_map) {

    assert(in.height == in.width && flood_map.height == flood_map.width);
    assert(in.height == flood_map.height);
    assert(grid_size>1);

    int original_size = in.height;
    int scaled_map_size = std::floor(original_size / grid_size);
    float sampled_distance = 0;

    NoiseMap* scaled_noise_map = new NoiseMap(scaled_map_size, scaled_map_size, 0.0);

    for (int s_x = 0; s_x < scaled_map_size; ++s_x) {
        for (int s_y = 0; s_y < scaled_map_size; ++s_y) {
            int min_x = std::floor( s_x * grid_size);
            int min_y = std::floor (s_y * grid_size);
            int max_x = std::ceil(s_x * grid_size + grid_size);
            int max_y = std::ceil(s_y * grid_size + grid_size);

            bool found_empty = false;
            for (int x = min_x; x <= max_x; ++x) {
                for (int y = min_y; y <= max_y; ++y) {
                    if (in[x][y]==0) {
                        found_empty = true;
                        sampled_distance = flood_map[x][y];
                        break;
                    }
                }
                if (found_empty) { break; }
            }

            if (!found_empty) {
                (*scaled_noise_map)[s_x][s_y] = 1.0;
            } else {
                // Check if in the vicinity theres a jump in flooding distance, this would mean that there's an "hard" wall
                // and this needs to be filled
                int min_sc_x = std::max<int>(0, std::floor( s_x * grid_size - grid_size));
                int min_sc_y = std::max<int>(0, std::floor (s_y * grid_size - grid_size));
                int max_sc_x = std::min<int>(original_size-1, std::ceil(s_x * grid_size + grid_size*2));
                int max_sc_y = std::min<int>(original_size-1, std::ceil(s_y * grid_size + grid_size*2));

                bool found_jump = false;
                for (int x = min_sc_x; x <= max_sc_x; ++x) {
                    for (int y = min_sc_y; y <= max_sc_y; ++y) {
                        if (flood_map[x][y]!=0) {
                            auto diff_from_sample = std::abs(sampled_distance - flood_map[x][y]);

                            if (diff_from_sample > grid_size*6) {
                                found_jump = true;
                                break;
                            }
                        }
                    }
                    if (found_jump) { break; }
                }

                if (found_jump) (*scaled_noise_map)[s_x][s_y] = 1.0;
            }
        }
    }

    scaled_noise_map->save_as_image("../out/scaled_mask.bmp",0,1);
    return scaled_noise_map;
}

NoiseMap *MiniaturePlanetoid::downscale_noisemap(const NoiseMap &in, float grid_size) {
    assert(in.height == in.width);
    assert(grid_size>1);

    int original_size = in.height;
    int scaled_map_size = std::floor(original_size / grid_size);

    NoiseMap* scaled_noise_map = new NoiseMap(scaled_map_size, scaled_map_size, 0.0);

    for (int s_x = 0; s_x < scaled_map_size; ++s_x) {
        for (int s_y = 0; s_y < scaled_map_size; ++s_y) {
            int min_x = std::floor( s_x * grid_size);
            int min_y = std::floor (s_y * grid_size);
            int max_x = std::ceil(s_x * grid_size + grid_size);
            int max_y = std::ceil(s_y * grid_size + grid_size);

            bool found_empty = false;
            for (int x = min_x; x <= max_x; ++x) {
                for (int y = min_y; y <= max_y; ++y) {
                    if (in[x][y]==0) {
                        found_empty = true;
                        break;
                    }
                }
                if (found_empty) { break; }
            }

            if (!found_empty) {
                (*scaled_noise_map)[s_x][s_y] = 1.0;
            }
        }
    }

    scaled_noise_map->save_as_image("../out/scaled_mask.bmp",0,1);
    return scaled_noise_map;
}

MarchingMap *MiniaturePlanetoid::get_scaled_secondary_marching_map() const {
    return m_scaled_secondary_marching_map;
}

float MiniaturePlanetoid::get_grid_size() const {
    return grid_size;
}
