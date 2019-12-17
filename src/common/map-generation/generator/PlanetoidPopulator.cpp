#include <Perlin.hpp>
#include "PlanetoidPopulator.hpp"
#include "SGE/utils/interpolation/Interpolator.hpp"
#include <bits/stdc++.h>


PlanetoidPopulator::PlanetoidPopulator(const MapGenInfo& map_gen_info, const MarchingMap &planetoid_square_grid, sge::Vec2<int> starting_point) {

    NoiseMap enemy_heat_map(planetoid_square_grid.width, planetoid_square_grid.height, 0);

    std::queue<sge::Vec2<int>> evaluation_queue;
    std::vector<sge::Vec2<int>> edge_coords;
    evaluation_queue.push(starting_point);
    int distance = 1;
    while (!evaluation_queue.empty()) {
        for (int i = 0; i < evaluation_queue.size(); ++i) {
            auto coords = evaluation_queue.front();
            evaluation_queue.pop();
            if (planetoid_square_grid[coords].get_type() != Square::FULL && enemy_heat_map[coords.x][coords.y]==0) {
                if(planetoid_square_grid[coords].is_edge()) {
                    edge_coords.emplace_back(coords.x, coords.y);
                }
                enemy_heat_map[coords.x][coords.y] = distance;


                if (coords.x>0)
                    evaluation_queue.emplace(coords.x-1, coords.y);
                if (coords.y>0)
                    evaluation_queue.emplace(coords.x, coords.y-1);
                if (coords.x<planetoid_square_grid.width-1)
                    evaluation_queue.emplace(coords.x+1, coords.y);
                if (coords.y<planetoid_square_grid.width-1)
                    evaluation_queue.emplace(coords.x, coords.y+1);

            }
        }
        distance++;
    }
    enemy_heat_map.normalize(0.3,1);

    enemy_heat_map.save_as_image("../out/enemy_heat_map_contours.bmp", 0,1);



    // Generate enemy noise
    NoiseMap enemy_noise(planetoid_square_grid.width, planetoid_square_grid.height);
    Perlin enemy_noise_generator(planetoid_square_grid.height);
    enemy_noise_generator.add_octave(4.5,1);
    enemy_noise_generator.fill_noise_map(enemy_noise, true);
    enemy_noise.apply_gradient_as_mask(
            CircularGradient(planetoid_square_grid.height / 2, 0, planetoid_square_grid.height / 2,
                             planetoid_square_grid.width / 2, 1, 0.3, new LinearInterpolator()));
    enemy_noise.normalize(0,1);
    enemy_noise.save_as_image("../out/enemy_noise.bmp", 0,1);

    enemy_heat_map*=enemy_noise;

    enemy_heat_map.save_as_image("../out/enemy_heat_map.bmp", 0,1);


    NoiseMap edge_spacing_map(planetoid_square_grid.width, planetoid_square_grid.height, 0);
    float max_val = 0;
    for (auto & edge_coord : edge_coords) {
        auto res = planetoid_square_grid.get_edge_safe_distance(edge_coord.x, edge_coord.y);
        if (res>max_val) max_val = res;
        edge_spacing_map[edge_coord.x][edge_coord.y] = res;
    }

    edge_spacing_map.save_as_image("../out/border_space.bmp", 0, max_val);

    // Get every different enemy size
    std::vector<float> enemy_sizes;
    for (int j = 0; j < map_gen_info.enemies_build_data.size(); ++j) {
        float space_needed = map_gen_info.enemies_build_data[j]->space_needed_on_edge();
        bool found = false;
        for (float enemy_size : enemy_sizes) {
            if (space_needed == enemy_size) {
                found = true;
                break;
            }
        }
        if (!found) {
            enemy_sizes.push_back(space_needed);
        }
    }

    std::sort(enemy_sizes.begin(), enemy_sizes.end(), std::greater<float>());

    // For every enemy size create a vector of build data and do a spawn session
    for (int k = 0; k < enemy_sizes.size(); ++k) {
        float target_size = enemy_sizes[k];
        std::vector<EnemyPersistentData*> this_pass_data_vector;
        for (int i = 0; i < map_gen_info.enemies_build_data.size(); ++i) {
            if (map_gen_info.enemies_build_data[i]->space_needed_on_edge() == target_size) {
                this_pass_data_vector.push_back(map_gen_info.enemies_build_data[i]);
            }
        }
        spawn_enemies(target_size, this_pass_data_vector, enemy_heat_map, edge_spacing_map, edge_coords, planetoid_square_grid);
    }

    enemy_heat_map.save_as_image("../out/enemy_heat_map_after_spawn.bmp", 0,1);




}

sge::Vec2<int> PlanetoidPopulator::find_highest_edge_coord(NoiseMap& values_map, std::vector<sge::Vec2<int>>& edge_coords) {
    float best_val = 0;
    sge::Vec2<int> best_coord;
    for (int i = 0; i < edge_coords.size(); ++i) {
        auto target_edge = edge_coords[i];
        auto target_val = values_map[target_edge.x][target_edge.y];
        if (target_val>best_val) {
            best_val = target_val;
            best_coord = target_edge;
        }
    }
    return best_coord;
}

void PlanetoidPopulator::spawn_enemies(float space_needed, std::vector<EnemyPersistentData*> enemies_data, NoiseMap &affinity_map,
                                       const NoiseMap &space_map, std::vector<coord>& edge_coords, const MarchingMap &planetoid_square_grid) {

    std::vector<coord> possible_coords;
    for (int i = 0; i < edge_coords.size(); ++i) {
        auto space_available_here = space_map[edge_coords[i].x][edge_coords[i].y];
        if (space_available_here>=space_needed) {
            possible_coords.push_back(edge_coords[i]);
        }
    }
    // Exaust the list of enemy to be spawned applying gradients in order to inhibit clumping
    for (int j = 0; j < enemies_data.size(); ++j) {
        auto target_coord = find_highest_edge_coord(affinity_map, possible_coords);
        affinity_map.apply_gradient_as_mask(CircularGradient(space_needed*3, space_needed*1.5, target_coord.x, target_coord.y, 0, 1,
                                                               new LinearInterpolator()));
        affinity_map.apply_gradient_as_mask(CircularGradient(space_needed*40, space_needed*3, target_coord.x, target_coord.y, 0.2, 1,
                                                             new RootInterpolator(2)));
        // Inibhition on a map level
        affinity_map.apply_gradient_as_mask(CircularGradient(affinity_map.width/4, 0, target_coord.x, target_coord.y, 0.8, 1,
                                                             new RootInterpolator(2)));
        enemies_data[j]->anchor_position = planetoid_square_grid[target_coord].get_edge_centers()[0];
        enemies_data[j]->angle = planetoid_square_grid[target_coord].get_edge_normal_rotations()[0]; // FIXME
        affinity_map[target_coord.x][target_coord.y] = 0;
        basic_enemies_coords.push_back(target_coord);
    }
}

