#ifndef NON_GRAVITAR_MULTISHOTENEMYPERSISTENTDATA_HPP
#define NON_GRAVITAR_MULTISHOTENEMYPERSISTENTDATA_HPP


#include "MultiShotEnemyHead.hpp"
#include "BasicEnemyPersistentData.hpp"

class MultiShotEnemyPersistentData : public BasicEnemyPersistentData {
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

    float get_max_shooting_angle() override {
        return M_PI/3.f;
    }
};


#endif //NON_GRAVITAR_MULTISHOTENEMYPERSISTENTDATA_HPP
