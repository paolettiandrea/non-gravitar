#ifndef NON_GRAVITAR_BASICENEMYBUILDDATA_HPP
#define NON_GRAVITAR_BASICENEMYBUILDDATA_HPP

#include <SGE/logic/Logic.hpp>
#include <enemies/Enemy.hpp>
#include "EnemyBuildData.hpp"
#include "EnemyHead.hpp"
#include "COLORS.hpp"

class BasicEnemyBuildData : public EnemyBuildData {


public:
    EnemyHead *new_head_logic() override {
        return new EnemyHead(this, this->head_load_paths());
    }

    BreakableObject_ConstructionData base_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic/basic_enemy__base", 3);
    }

    BreakableObject_ConstructionData head_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic/basic_enemy__head", 3);
    }

    BreakableObject_ConstructionData cannon_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic/basic_cannon__cannon", 3);
    }

    BreakableObject_ConstructionData bullet_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic/basic_cannon__bullet", 3);
    }

    float get_view_range() override                     { return 30; }

    float space_needed_on_edge() override               { return 0.6; }

    sf::Color get_minimap_pin_color() override          { return sf::Color(200, 30, 30); }

    float get_minimap_pin_size() override               { return 1; }

    const ColorPalette *get_enemy_palette() override    { return &BASIC_ENEMY_PALETTE; }

    float get_shooting_speed() override                 { return 5.0; }

    float get_max_shooting_angle() override             { return M_PI_2; }

    float get_shooting_period() override                { return 3.0; }


    EnemyOffsets get_offsets() override {
        EnemyOffsets enemy_offsets;
        enemy_offsets.head_offset =                     sge::Vec2<float>(0,1.1);
        enemy_offsets.cannon_offset =                   sge::Vec2<float>(0,-0.2);
        enemy_offsets.shooting_offset =                 sge::Vec2<float>(0,1);
        return enemy_offsets;
    }

    ExplosionInfo get_explosion_info() override {
        ExplosionInfo info;
        info.explosion_force = 3;
        info.explosion_radius = 2;
        return info;
    }



};
#endif //NON_GRAVITAR_BASICENEMYBUILDDATA_HPP
