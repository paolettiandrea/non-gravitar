#ifndef NON_GRAVITAR_ENEMYPERSISTENTDATA_HPP
#define NON_GRAVITAR_ENEMYPERSISTENTDATA_HPP

#include <PhysicsObject.hpp>
#include <scaled-planetoid/minimap/MinimapTraced_I.hpp>
#include "SGE/Vec2.hpp"
#include "SGE/logic/Logic.hpp"
class EnemyPersistentData: public MinimapTraced_I {
public:
    virtual ~EnemyPersistentData() {
    }
    virtual float space_needed_on_edge() = 0;

    virtual BreakableObject_ConstructionData base_load_paths() = 0;
    virtual BreakableObject_ConstructionData head_load_paths() = 0;
    virtual BreakableObject_ConstructionData cannon_load_paths() = 0;
    virtual BreakableObject_ConstructionData bullet_load_paths() = 0;
    virtual sf::Color get_minimap_pin_color() = 0;
    virtual float get_minimap_pin_size() = 0;

    sge::Vec2<float> get_position_relative_to_planetoid() override {
        return anchor_position;
    }

    std::vector<sf::Vertex> get_minimap_model_vertices() override {
        sf::Color color = get_minimap_pin_color();
        float size = get_minimap_pin_size();
        return {sf::Vertex(sf::Vector2f(size,size), color),
        sf::Vertex(sf::Vector2f(-size,size), color),
        sf::Vertex(sf::Vector2f(-size,-size), color),
        sf::Vertex(sf::Vector2f(size,-size), color)};
    }

    // structural
    virtual sge::Vec2<float> head_offset() { return sge::Vec2<float>(0,0); };

    sge::Vec2<float> anchor_position;
    float angle;

    bool destroyed = false;
};
#endif //NON_GRAVITAR_ENEMYPERSISTENTDATA_HPP
