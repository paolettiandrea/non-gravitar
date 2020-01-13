#ifndef NON_GRAVITAR_MULTISHOTENEMYBUILDDATA_HPP
#define NON_GRAVITAR_MULTISHOTENEMYBUILDDATA_HPP


#include <game-scene/enemies/parts/head/MultiShotEnemyHead.hpp>
#include "BasicEnemyBuildData.hpp"

class MultiShotEnemyBuildData : public BasicEnemyBuildData {
public:
    EnemyHead *new_head_logic() override {
        return new MultiShotEnemyHead(this, this->head_load_paths());
    }

    BreakableObject_ConstructionData base_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/multishot/multishot_enemy__base", 3);
    }

    BreakableObject_ConstructionData head_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/multishot/multishot_enemy__head", 3);
    }

    EnemyOffsets get_offsets() override {
        EnemyOffsets enemy_offsets;
        enemy_offsets.head_offset =                     sge::Vec2<float>(0,1.25);
        enemy_offsets.cannon_offset =                   sge::Vec2<float>(0,0);
        enemy_offsets.shooting_offset =                 sge::Vec2<float>(0,1);
        return enemy_offsets;
    }


};


#endif //NON_GRAVITAR_MULTISHOTENEMYBUILDDATA_HPP
