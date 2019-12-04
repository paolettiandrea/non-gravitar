#ifndef PERLIN_TESTS_SQUARE_HPP
#define PERLIN_TESTS_SQUARE_HPP


#include <vector>

#include "Square.hpp"
#include "NoiseMap.hpp"
#include "SGE/Path.hpp"

typedef sge::Vec2<int> coord;

class MarchingMap {
public:
    MarchingMap(const NoiseMap &map, float threshold, bool invert);


    const std::vector<sge::Path> &get_paths() const;

    Square& get_square(unsigned int row, unsigned int column);
    const Square& get_square(unsigned int row, unsigned int column) const;

    const unsigned int width, height;

    Square& operator[](sge::Vec2<int> coords);
    const Square& operator[](sge::Vec2<int> coords) const;

    /*!
     * /brief Returns the shortest distance from the center of the given edge square to the end of the straight edge.
     * @param row
     * @param column
     * @return
     */
    const float get_edge_safe_distance(unsigned int row, unsigned int column) const;

private:
    std::vector<sge::Path> paths;
    std::vector<std::vector<Square>> square_grid;

    const coord get_next_square_coords(coord pointed_square, coord avoid_square, float target_rotation) const;
    const std::vector<coord> get_angle_matches(coord pointed_square, float target_rotation) const;
    const int recursive_stepper(coord point, coord exclude, float rot_target, int counter) const;

};


#endif //PERLIN_TESTS_SQUARE_HPP
