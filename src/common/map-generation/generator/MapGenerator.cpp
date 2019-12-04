#include "MapGenerator.hpp"
#include "EllipticGradient.hpp"
#include "RegionDistanceData.hpp"
#include <map>
#include <CircularGradient.hpp>
#include <queue>
#include <climits>


MapGenerator::MapGenerator(const MapGenInfo& map_gen_info)
        : Loggable("MapGenerator"), m_size(map_gen_info.size), surface_mask(map_gen_info.size,map_gen_info.size)
        , tunnel_noise(map_gen_info.size,map_gen_info.size), tunnel_mask(map_gen_info.size,map_gen_info.size)
        , combined_mask(map_gen_info.size, map_gen_info.size), secondary_fill_mask(map_gen_info.size, map_gen_info.size)

{

    generate_surface_mask();
    surface_mask.save_as_image("../out/1 surface mask.bmp",0,1);

    generate_tunnel_noise();
    tunnel_noise.save_as_image("../out/2 tunnel noise.bmp",0,1);


    update_combination_masks();
    tunnel_mask.save_as_image("../out/3 tunnel mask.bmp",0,1);
    combined_mask.save_as_image("../out/4 combined mask.bmp",0,1);
    secondary_fill_mask.save_as_image("../out/4a-secondary-fill-mask.bmp", 0, 1);

    define_regions();
    discard_regions(map_gen_info.min_cave_volume, map_gen_info.min_filled_region_volume);

    bool done = false;
    int linking_iterations_counter = 0;
    bool exclude_surface = true;

    while (!done) {
        LOG_INFO << "Starting planetoid generation iteration";
        linking_iterations_counter++;

        link_caves(exclude_surface);
        tunnel_noise.save_as_image("../out/" + std::to_string(linking_iterations_counter*4) + " linking (iteration " + std::to_string(linking_iterations_counter) + ").bmp", 0, 1);

        update_combination_masks();
        tunnel_mask.save_as_image("../out/" + std::to_string(linking_iterations_counter*4+1) + " linked tunnel mask.bmp", 0, 1);
        combined_mask.save_as_image("../out/" + std::to_string(linking_iterations_counter*4+2) + " linked combined mask.bmp", 0, 1);

        define_regions();
        discard_regions(map_gen_info.min_cave_volume, map_gen_info.min_filled_region_volume);

        combined_mask.save_as_image("../out/" + std::to_string(linking_iterations_counter*4+3) + " small regions excluded.bmp", 0, 1);

        if (cave_regions.size()<=2) {
            if (!cave_regions[0].contains(sge::Vec2<int>(0,0))) exclude_surface = false;
            if (cave_regions.size()==1) done = true;
        }
    }

    calculate_final_stats();

    find_entrances();
}

void MapGenerator::generate_surface_mask() {

    Perlin surface_perlin(m_size/10.f);
    surface_perlin.simple_setup(3,0.6,2);
    surface_perlin.fill_noise_map(surface_mask, true);

    CircularGradient gradient (m_size/2.f, m_size/3.f, m_size/2.f,m_size/2.f, 1.f, 0, new RootInterpolator(2));
    NoiseMap gradient_map(m_size,m_size, 1.f);
    gradient_map.apply_gradient_as_mask(gradient);

    surface_mask.apply_gradient_as_mask(gradient);
    surface_mask.weighted_average(gradient_map,gradient);

    surface_mask.normalize(0,1);
    surface_mask.apply_threshold(0.5,1,0);

    // Calculate whole planetoid relevant info
    Region planetoid_region;
    Matrix2D<bool> temp_check_matrix (surface_mask.width,surface_mask.height);
    planetoid_region.flood_fill(surface_mask, 0, 0, 0, temp_check_matrix);

    m_whole_planet_volume = m_size*m_size - planetoid_region.get_volume();
    auto border_points = planetoid_region.get_border_points();
    for (int i = 0; i < border_points.size(); ++i) {
        m_whole_planet_surface_points.push_back(border_points[i]);
    }
}

void MapGenerator::update_combination_masks() {
    tunnel_mask = tunnel_noise;
    tunnel_mask.apply_threshold(0.5f,1,0);

    combined_mask = surface_mask;
    combined_mask.apply_noisemap_as_mask(tunnel_mask);

    secondary_fill_mask = tunnel_noise;
    secondary_fill_mask.apply_threshold(0.7f, 1, 0);
    secondary_fill_mask.apply_noisemap_as_mask(surface_mask);
}

void MapGenerator::define_regions() {
    Matrix2D<bool> checked_flags_matrix(combined_mask.width,combined_mask.height);
    for (int x = 0; x < combined_mask.width; ++x) {
        for (int y = 0; y < combined_mask.height; ++y) {
            checked_flags_matrix[x][y] = false;
        }
    }

    cave_regions.clear();
    filled_regions.clear();

    // First of all the central and (often if not always) main cave at the first place
    cave_regions.emplace_back();
    cave_regions[0].flood_fill(combined_mask,combined_mask.width/2,combined_mask.height/2, 0.f, checked_flags_matrix);

    // Flood-fill all the other caves
    for (int x = 0; x < combined_mask.width; ++x) {
        for (int y = 0; y < combined_mask.height; ++y) {
            if (combined_mask[x][y]==0.f && !checked_flags_matrix[x][y]) {
                cave_regions.emplace_back();
                cave_regions.back().flood_fill(combined_mask, x, y, 0.f, checked_flags_matrix);
            }
        }
    }

    for (int x = 0; x < combined_mask.width; ++x) {
        for (int y = 0; y < combined_mask.height; ++y) {
            if (combined_mask[x][y]==1.f && !checked_flags_matrix[x][y]) {
                filled_regions.emplace_back();
                filled_regions.back().flood_fill(combined_mask, x, y, 1.f, checked_flags_matrix);
            }
        }
    }
}

void MapGenerator::link_caves(bool exclude_surface_points) {
     bool already_incorporated_region[cave_regions.size()];
    for (int k = 0; k < cave_regions.size(); ++k) {
        already_incorporated_region[k] = false;
    }

    // Check for the closest region which wasn't already incorporated in another one
    for (int i = 0; i < cave_regions.size(); ++i) {
        RegionDistanceData best;
        int best_index = -1;
        best.pseudo_distance = std::numeric_limits<float>::max();
        for (int j = 0; j < cave_regions.size(); ++j) {
            if (i!=j && !already_incorporated_region[j]) {
                auto res = Region::pseudo_distance(cave_regions[i], cave_regions[j]);
                bool good_to_go = true;
                if (exclude_surface_points && (is_surface_border(res.p1) || is_surface_border(res.p2)))  good_to_go = false;
                if (res.pseudo_distance < best.pseudo_distance && good_to_go) {
                    best = res;
                    best_index = j;
                }
            }
        }
        if (best_index!=-1 && !cave_regions[i].is_connected(cave_regions[best_index])) {
            cave_regions[i].set_connected(cave_regions[best_index]);
            cave_regions[best_index].set_connected(cave_regions[i]);


            EllipticGradient gradient(0.5,1,new RootInterpolator(4), best.p1.x, best.p1.y, best.p2.x, best.p2.y,4);
            tunnel_noise.apply_gradient_as_mask(gradient);
        }
    }
}

void MapGenerator::discard_regions(unsigned int min_cave_volume, unsigned int min_filled_volume) {
    int size = cave_regions.size();
    for (int i = size-1; i >=0; --i) {
        if (cave_regions[i].get_volume()<min_cave_volume) {
            cave_regions[i].fill_with_val(combined_mask,1.f);
            cave_regions.erase(cave_regions.begin()+i);
        }
    }

    for (int i = cave_regions.size()-1; i >=0; --i) {
        if (cave_regions[i].get_volume()<min_filled_volume) {
            cave_regions[i].fill_with_val(combined_mask,0.f);
            cave_regions.erase(cave_regions.begin()+i);
        }
    }
}

void MapGenerator::generate_tunnel_noise() {

    float tunnel_scale = 30;
    Perlin perlin_generator(tunnel_scale);

    perlin_generator.simple_setup(3,0.4,2);

    perlin_generator.fill_noise_map(tunnel_noise, true);

    CircularGradient central_hole_gradient(m_size/10.f, m_size/100.f, m_size/2.f, m_size/2.f, 0, 1, new RootInterpolator(2));
    tunnel_noise.apply_gradient_as_mask(central_hole_gradient);
    tunnel_noise.normalize(0,1);

    CircularGradient tunnel_fade_gradient(m_size/2.f, m_size/4.f, m_size/2.f, m_size/2.f, 0, 1, new RootInterpolator(1));
    tunnel_noise.weighted_average(1.f,tunnel_fade_gradient);
}

bool MapGenerator::is_surface_border(sge::Vec2<int> point) {
    for (int i = 0; i < m_whole_planet_surface_points.size(); ++i) {
        if (m_whole_planet_surface_points[i]==point) return true;
    }
    return false;
}

void MapGenerator::calculate_final_stats() {
    define_regions();
    int cave_volume = cave_regions[0].get_volume() - (m_size*m_size - m_whole_planet_volume);
    std::cout << "Planet generation done.\n"
                 "Whole initial volume: " << m_whole_planet_volume << " || Cave volume: " << cave_volume << "|| Caved percentage: " << cave_volume/(float)m_whole_planet_volume*100 << "%" << std::endl;
}

void MapGenerator::find_entrances() {
    std::vector<sge::Vec2<int>> surface_border;
    for (int x = 0; x < m_size; ++x) {
        for (int y = 0; y < m_size; ++y) {
            if (surface_mask[x][y]==1){
                if (surface_mask[x-1][y]==0 || surface_mask[x-1][y+1]==0 || surface_mask[x-1][y-1]==0
                    || surface_mask[x][y]==0 || surface_mask[x][y+1]==0 || surface_mask[x][y-1]==0
                    || surface_mask[x+1][y]==0 || surface_mask[x+1][y+1]==0 || surface_mask[x+1][y-1]==0) {
                    surface_border.emplace_back(x,y);
                }
            }
        }
    }

    NoiseMap out_map(m_size, m_size, 0);
    // Find the planet edge points that are not filled anymore and save their coord as possible entrances
    std::vector<sge::Vec2<int>> possible_entrances;
    for (int i = 0; i < surface_border.size(); ++i) {
        if (combined_mask[surface_border[i].x][surface_border[i].y]==0) {
            possible_entrances.emplace_back(surface_border[i]);
            out_map[surface_border[i].x][surface_border[i].y] = 1;
        } else {
            out_map[surface_border[i].x][surface_border[i].y] = 0.5;
        }
    }



    NoiseMap distance_from_center_map(m_size, m_size);
    distance_from_center_map = combined_mask;

    distance_flood_fill(distance_from_center_map, sge::Vec2<int>(m_size / 2, m_size / 2));

    // Find the possible entrance closest to the center
    int best_distance = INT_MAX;
    for (int j = 0; j < possible_entrances.size(); ++j) {
        auto focus = possible_entrances[j];
        if (best_distance > distance_from_center_map[focus.x][focus.y]) {
            entry_coords = possible_entrances[j];
            best_distance = distance_from_center_map[possible_entrances[j].x][possible_entrances[j].y];
        }
    }


    out_map[entry_coords.x][entry_coords.y] = 0.7;
    out_map.save_as_image("../out/border-analysis.bmp", 0,1);



}

void MapGenerator::distance_flood_fill(NoiseMap &mask, sge::Vec2<int> starting_point) {

    std::queue<sge::Vec2<int>> points_to_evaluate;

    int distance = 1;

    points_to_evaluate.push(starting_point);

    while (!points_to_evaluate.empty()) {
        for (int i = 0; i < points_to_evaluate.size(); ++i) {
            sge::Vec2<int> focus = points_to_evaluate.front();
            points_to_evaluate.pop();

            if (mask[focus.x][focus.y]==0) {
                mask[focus.x][focus.y] = distance;

                if (focus.x>0) points_to_evaluate.emplace(focus.x-1, focus.y);
                if (focus.y>0) points_to_evaluate.emplace(focus.x, focus.y-1);

                if (focus.x < mask.width - 1) points_to_evaluate.emplace(focus.x + 1, focus.y);
                if (focus.y < mask.height - 1) points_to_evaluate.emplace(focus.x, focus.y + 1);
            }
        }
        distance++;
    }

    mask.save_as_image("../out/flood_fill.bmp", 0,distance);
}




