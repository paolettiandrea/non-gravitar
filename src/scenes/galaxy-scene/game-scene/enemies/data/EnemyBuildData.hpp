#ifndef NON_GRAVITAR_ENEMYBUILDDATA_HPP
#define NON_GRAVITAR_ENEMYBUILDDATA_HPP

#include <PhysicsObject.hpp>
#include <scaled-planetoid/minimap/MinimapTraced_I.hpp>
#include <game-scene/breakable/handler/BreakHandler.hpp>
#include <utility-classes/ColorPalette.hpp>
#include "SGE/Vec2.hpp"
#include "SGE/logic/Logic.hpp"

class EnemyHead;

struct EnemyOffsets {
    sge::Vec2<float> head_offset;
    sge::Vec2<float> cannon_offset;
    sge::Vec2<float> shooting_offset;
};

class EnemyBuildData: public MinimapTraced_I {
public:
    virtual ~EnemyBuildData() {
    }
    virtual float space_needed_on_edge() = 0;

    virtual BreakableObject_ConstructionData base_load_paths() = 0;
    virtual BreakableObject_ConstructionData head_load_paths() = 0;
    virtual BreakableObject_ConstructionData cannon_load_paths() = 0;
    virtual BreakableObject_ConstructionData bullet_load_paths() = 0;
    virtual sf::Color get_minimap_pin_color() = 0;
    virtual float get_minimap_pin_size() = 0;
    virtual ExplosionInfo get_explosion_info() = 0;
    virtual EnemyHead* new_head_logic() = 0;
    virtual const ColorPalette* get_enemy_palette() = 0;
    virtual float get_shooting_speed() = 0;
    virtual EnemyOffsets get_offsets() = 0;
    virtual float get_head_turning_duration() { return 0.5; }
    virtual float get_view_range() = 0;
    virtual float get_max_shooting_angle() = 0;
    float get_min_shooting_angle() { return - get_max_shooting_angle(); };
    virtual float get_shooting_period() = 0;

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

    sge::Vec2<float> anchor_position;
    float angle;

    bool destroyed = false;
};
#endif //NON_GRAVITAR_ENEMYBUILDDATA_HPP
