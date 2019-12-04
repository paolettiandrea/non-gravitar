#ifndef PERLIN_TESTS_MAPGENERATOR_HPP
#define PERLIN_TESTS_MAPGENERATOR_HPP

#ifndef MAPGENERATOR_CAVE_VOLUME_HARD_MIN
#define MAPGENERATOR_CAVE_VOLUME_HARD_MIN 10
#endif

#include "NoiseMap.hpp"
#include "Perlin.hpp"
#include "Region.hpp"
#include "MapGenInfo.hpp"

class MapGenerator : public utils::log::Loggable{
public:
explicit    MapGenerator(const MapGenInfo& map_gen_info) ;

    NoiseMap combined_mask;
    NoiseMap secondary_fill_mask;
    sge::Vec2<int> entry_coords;
private:
    int m_size;
    NoiseMap surface_mask;
    NoiseMap tunnel_noise;
    NoiseMap tunnel_mask;


    /*!
     * \brief A list of the hollow regions of the map.
     * \details The first Region is guaranteed to be the central cave (since it's flooded from the center of the map),
     * but it's not guaranteed to reach the surface of the planet
     */
    std::vector<Region> cave_regions;
    std::vector<Region> filled_regions;


    int m_whole_planet_volume = 0;
    std::vector<sge::Vec2<int>> m_whole_planet_surface_points;
    std::vector<sge::Vec2<int>> entrances;


    void generate_surface_mask();

    void generate_tunnel_noise();

    void update_combination_masks();

    void define_regions();

    void discard_regions(unsigned int min_cave_volume, unsigned int min_filled_volume);

    void link_caves(bool exclude_surface_points);

    void find_entrances();

    /*!
     * \param point
     * \return true if the given point was part of the border of the planet BEFORE tunnels were applied, false otherwise
     */
    bool is_surface_border(sge::Vec2<int> point);

    void calculate_final_stats();

    void distance_flood_fill(NoiseMap& mask, sge::Vec2<int> starting_point);

};


#endif //PERLIN_TESTS_MAPGENERATOR_HPP
