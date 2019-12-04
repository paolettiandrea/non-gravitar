//
// Created by andrea on 6/6/19.
//

#ifndef PERLIN_TESTS_REGION_HPP
#define PERLIN_TESTS_REGION_HPP

#include "SGE/Vec2.hpp"
#include <vector>
#include "queue"
#include "NoiseMap.hpp"
#include "SGE/utils/Matrix2D.hpp"
#include "RegionDistanceData.hpp"
#include <limits>
#include <ostream>


class Region {
public:
    Region() {
        m_unique_index = unique_index_counter++;
    };

    void flood_fill(const NoiseMap& map, int x, int y, float target_val, Matrix2D<bool>& checked_flags_matrix);

    static RegionDistanceData pseudo_distance(Region& region1, Region& region2);

    int get_volume() { return m_volume; }

    void set_connected(const Region& other_region);

    bool is_connected(const Region& other_region);

    friend std::ostream& operator<<(std::ostream& os, const Region& region);

    std::vector<sge::Vec2<int>> get_border_points() { return  m_border_points; }

    int unique_id() { return  m_unique_index; }

    bool contains(sge::Vec2<int> point);

    void fill_with_val (NoiseMap& map, float val);


private:
    static int unique_index_counter;

    std::vector<sge::Vec2<int>> m_points;
    std::vector<sge::Vec2<int>> m_border_points;
    int m_volume = 0;
    std::vector<int> connected_rooms;
    int m_unique_index;
};



#endif //PERLIN_TESTS_REGION_HPP
