#ifndef NON_GRAVITAR_BASICENEMYBUILDDATA_HPP
#define NON_GRAVITAR_BASICENEMYBUILDDATA_HPP

#include <SGE/logic/Logic.hpp>
#include <enemies/Enemy.hpp>
#include "EnemyBuildData.hpp"
#include "EnemyHead.hpp"
#include "COLORS.hpp"

class BasicEnemyBuildData : public EnemyBuildData {


public:

    float space_needed_on_edge() override {
        return 0.6;
    }

    BreakableObject_ConstructionData base_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic_enemy__base", 3);
    }

    BreakableObject_ConstructionData head_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic_enemy__head", 3);
    }

    BreakableObject_ConstructionData cannon_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic_enemy__cannon", 3);
    }

    BreakableObject_ConstructionData bullet_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic_enemy__bullet", 3);
    }

    sf::Color get_minimap_pin_color() override {
        return sf::Color(200, 30, 30);
    }

    float get_minimap_pin_size() override {
        return 1;
    }

    ExplosionInfo get_explosion_info() override {
        ExplosionInfo info;
        info.explosion_force = 3;
        info.explosion_radius = 2;
        return info;
    }

    EnemyHead *new_head_logic(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data) override {
        return new EnemyHead(whole_data, my_breakable_geom_data);
    }

    const ColorPalette *get_enemy_palette() override {
        return &BASIC_ENEMY_PALETTE;
    }

    float get_shooting_speed() override {
        return 5.0;
    }

    sge::Vec2<float> get_shoot_offset() override {
        return sge::Vec2<float>(0, 1);
    }

    sge::Vec2<float> head_offset() override {
        return sge::Vec2<float>(0, 1);
    }



};
#endif //NON_GRAVITAR_BASICENEMYBUILDDATA_HPP
