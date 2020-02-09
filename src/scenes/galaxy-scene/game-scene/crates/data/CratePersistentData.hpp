#ifndef NON_GRAVITAR_CRATEPERSISTENTDATA_HPP
#define NON_GRAVITAR_CRATEPERSISTENTDATA_HPP

#include <SGE/Vec2.hpp>
#include <utility-logic/PhysicsObject.hpp>
#include "Player.hpp"
#include "COLORS.hpp"


struct CratePersistentData : public MinimapTraced_I {

    sge::Vec2<float> position;

    bool destroyed = false;

    virtual ~CratePersistentData() {

    }

    virtual BreakableObject_ConstructionData get_base_construction_data() {
        return BreakableObject_ConstructionData("./res/models/crates/crate__base", 1);
    }

    virtual std::string get_content_smesh_path() { return ""; }
    virtual sf::Color get_overlay_color() { return sf::Color::White; }

    virtual void apply_effect_on_player(Player* player_logic) = 0;

    sge::Vec2<float> get_position_relative_to_planetoid() override {
        return position;
    }

    virtual float get_content_logo_scale() { return 1.f; };

    std::vector<sf::Vertex> get_minimap_model_vertices() override {
        float size = NG_MINIMAP_DEFAULT_PIN_SIZE;
        return {sf::Vertex(sf::Vector2f(size,size), NG_CRATE_PIN_COLOR),
                sf::Vertex(sf::Vector2f(-size,size), NG_CRATE_PIN_COLOR),
                sf::Vertex(sf::Vector2f(-size,-size), NG_CRATE_PIN_COLOR),
                sf::Vertex(sf::Vector2f(size,-size), NG_CRATE_PIN_COLOR)};
    }

};

#endif //NON_GRAVITAR_CRATEPERSISTENTDATA_HPP
