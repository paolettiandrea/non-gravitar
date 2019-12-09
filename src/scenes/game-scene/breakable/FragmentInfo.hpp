#ifndef NON_GRAVITAR_FRAGMENTINFO_HPP
#define NON_GRAVITAR_FRAGMENTINFO_HPP

#include <SGE/Path.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "TriangleOverlap.hpp"
#include <SGE/components/graphics/VertArray.hpp>

class FragmentInfo {
public:

    FragmentInfo(VertArray_H vert_array, int i, int max_triangles) {
        auto sum = vert_array->get_vert_array()[i].position + vert_array->get_vert_array()[i+1].position + vert_array->get_vert_array()[i+2].position;
        world_center = sge::Vec2<float>(sum.x / 3, -sum.y / 3);

        fragment_render_layer = vert_array->get_layer_id();

        this->max_triangles = max_triangles;

        for (int j = 0; j < 3; ++j) {
            const sf::Vertex &target_vertex = vert_array->get_vert_array()[i + j];
            const auto target_local_point = vert_array->get_local_points()[i + j];
            world_positions[j].first = target_vertex.position.x;
            world_positions[j].second = -target_vertex.position.y;
            colors[j] = target_vertex.color;
        }
    }

    TriPoint world_positions[3];
    sge::Vec2<float> world_center;

    sf::Color colors[3];
    std::string fragment_render_layer;

    unsigned int max_triangles;


    bool shares_border(const FragmentInfo& other_fragment) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int next_i = i+1;
                if (next_i == 3) next_i = 0;
                int next_j = j + 1;
                if (next_j == 3) next_j = 0;

                if ((world_positions[i] == other_fragment.world_positions[j] && world_positions[next_i] == other_fragment.world_positions[next_j])
                    || (world_positions[next_i] == other_fragment.world_positions[j] && world_positions[i] == other_fragment.world_positions[next_j])) {
                    return true;
                }
            }
        }
        return false;
    }
};


#endif //NON_GRAVITAR_FRAGMENTINFO_HPP
