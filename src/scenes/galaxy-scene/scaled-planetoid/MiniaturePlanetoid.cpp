#include "MiniaturePlanetoid.hpp"
#include <cmath>

MiniaturePlanetoid::MiniaturePlanetoid(PlanetoidPersistentData *data, float grid_size) {
    persistent_data = data;
    this->grid_size = grid_size;

    NoiseMap& flooded_map = persistent_data->map_generator.flooded_map;


    NoiseMap* scaled_noise_map = downscale_noisemap(data->map_generator.combined_mask, grid_size,data->map_generator.flooded_map);
    m_scaled_marching_map = new MarchingMap(*scaled_noise_map, 0.5, true);

    NoiseMap* scaled_secondary_noise_map = downscale_noisemap(data->map_generator.secondary_fill_mask, grid_size);
    m_scaled_secondary_marching_map = new MarchingMap(*scaled_secondary_noise_map, 0.5, true);

    scaled_fog_noisemap = downscale_noisemap(data->map_generator.surface_mask, grid_size);

    int background_outline_thickness = 3;

    // Thicken the fog outline
    NoiseMap no(scaled_fog_noisemap->width, scaled_noise_map->height, 0.0);
    for (int x = 0; x < scaled_fog_noisemap->width; ++x) {
        for (int y = 0; y < scaled_fog_noisemap->height; ++y) {
            if ((*scaled_fog_noisemap)[x][y] != 0.0) {
                no[x][y] = 1.0;
            }

            int min_sc_x = std::max<int>(0, x - background_outline_thickness);
            int min_sc_y = std::max<int>(0, y - background_outline_thickness);
            int max_sc_x = std::min<int>(no.width-1, x + background_outline_thickness);
            int max_sc_y = std::min<int>(no.height-1, y + background_outline_thickness);

            bool found = false;
            for (int x1 = min_sc_x; x1 <= max_sc_x; ++x1) {
                for (int y1 = min_sc_y; y1 <= max_sc_y; ++y1) {
                    if ((*scaled_fog_noisemap)[x1][y1] != 0) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }

            if (found) no[x][y] = 1.0;
        }
    }

    *scaled_fog_noisemap = no;

    scaled_fog_background_marching_map = new MarchingMap(no, 0.5, true);

    delete (scaled_noise_map);
    delete (scaled_secondary_noise_map);
}

void MiniaturePlanetoid::on_start() {
    vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    make_geometry_dirty();
}

void MiniaturePlanetoid::on_update() {
    if (dirty_geometry_flag) {
        clean_geometry();
    }
}

MiniaturePlanetoid::~MiniaturePlanetoid() {
    delete (m_scaled_marching_map);
    delete (m_scaled_secondary_marching_map);
    delete (scaled_fog_noisemap);
    delete (scaled_fog_background_marching_map);
}

MiniaturePlanetoid::MiniaturePlanetoid(MiniaturePlanetoid *base) {
    grid_size = base->grid_size;
    m_scaled_marching_map = base->m_scaled_marching_map;
    m_scaled_secondary_marching_map = base->m_scaled_secondary_marching_map;
    persistent_data = base->persistent_data;

    scaled_fog_noisemap = base->scaled_fog_noisemap;

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
    return scaled_noise_map;
}

MarchingMap *MiniaturePlanetoid::get_scaled_secondary_marching_map() const {
    return m_scaled_secondary_marching_map;
}

float MiniaturePlanetoid::get_grid_size() const {
    return grid_size;
}

bool MiniaturePlanetoid::burn_fog(sge::Camera *camera) {
    auto scaled_pos = camera->get_center() / grid_size;

    auto vertical_size = camera->get_vertical_size()/2;
    auto horizontal_size = camera->get_vertical_size() * camera->get_ratio() / 2.0;

    int min_sc_x = std::max<int>(0, std::floor(scaled_pos.x - (horizontal_size/grid_size)));
    int min_sc_y = std::max<int>(0, std::floor (scaled_pos.y - (vertical_size/grid_size)));
    int max_sc_x = std::min<int>(scaled_fog_noisemap->width, std::ceil(scaled_pos.x + (horizontal_size/grid_size)));
    int max_sc_y = std::min<int>(scaled_fog_noisemap->height, std::ceil(scaled_pos.y + (vertical_size/grid_size)));

    bool fog_map_changed = false;
    for (int x = min_sc_x; x < max_sc_x; ++x) {
        for (int y = min_sc_y; y < max_sc_y; ++y) {
            if ((*scaled_fog_noisemap)[x][y] != 0) {
                (*scaled_fog_noisemap)[x][y] = 0;
                fog_map_changed = true;
            }
        }
    }
    return fog_map_changed;
}

NoiseMap *MiniaturePlanetoid::get_scaled_fog_noisemap() const {
    return scaled_fog_noisemap;
}

MarchingMap *MiniaturePlanetoid::get_scaled_fog_background_marching_map() const {
    return scaled_fog_background_marching_map;
}

void MiniaturePlanetoid::clean_geometry() {
    vert_array->clear();
    Planetoid::assemble_vert_array(vert_array, *m_scaled_marching_map, persistent_data->map_gen_info.palette.primary);
    Planetoid::assemble_vert_array(vert_array, *m_scaled_secondary_marching_map, persistent_data->map_gen_info.palette.dark);
    Planetoid::assemble_vert_array(vert_array, MarchingMap(*scaled_fog_noisemap, 0.5, true), persistent_data->map_gen_info.palette.light);
    dirty_geometry_flag = false;
}

void MiniaturePlanetoid::make_geometry_dirty() {
    dirty_geometry_flag = true;
}
