#ifndef NON_GRAVITAR_SNIPERENEMYBUILDDATA_HPP
#define NON_GRAVITAR_SNIPERENEMYBUILDDATA_HPP

#include "BasicEnemyPersistentData.hpp"
#include "SniperEnemyHead.hpp"

class SniperEnemyBuildData : public BasicEnemyPersistentData {
public:
    EnemyHead *new_head_logic() override {
        return new SniperEnemyHead(this, this->head_load_paths());
    }

    float get_shooting_speed() override                 { return 70; }

    float get_view_range() override                     { return BasicEnemyPersistentData::get_view_range() * 2; }

    EnemyOffsets get_offsets() override {
        EnemyOffsets enemy_offsets;
        enemy_offsets.head_offset =                     sge::Vec2<float>(0,1.25);
        enemy_offsets.cannon_offset =                   sge::Vec2<float>(0,0.1);
        enemy_offsets.shooting_offset =                 sge::Vec2<float>(0,1.8);
        return enemy_offsets;
    }

    const ColorPalette *get_enemy_palette() override {
        return &SNIPER_ENEMY_PALETTE;
    }

    BreakableObject_ConstructionData base_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/sniper/sniper_enemy__base", 3);
    }

    BreakableObject_ConstructionData head_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/sniper/sniper_enemy__head", 3);
    }

    BreakableObject_ConstructionData cannon_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/sniper/sniper_cannon__cannon", 3);
    }

    BreakableObject_ConstructionData bullet_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/sniper/sniper_cannon__bullet", 1);
    }

};
#endif //NON_GRAVITAR_SNIPERENEMYBUILDDATA_HPP
