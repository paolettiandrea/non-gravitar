#ifndef NON_GRAVITAR_MINIMAPTRACED_I_HPP
#define NON_GRAVITAR_MINIMAPTRACED_I_HPP

#include <SGE/Vec2.hpp>
#include <SFML/Graphics.hpp>

class MinimapTraced_I {
public:
    virtual sge::Vec2<float> get_position_relative_to_planetoid() = 0;
    virtual std::vector<sf::Vertex> get_minimap_model_vertices() = 0;
};

#endif //NON_GRAVITAR_MINIMAPTRACED_I_HPP
