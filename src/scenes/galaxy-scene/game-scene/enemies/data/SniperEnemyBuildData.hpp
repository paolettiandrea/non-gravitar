#ifndef NON_GRAVITAR_SNIPERENEMYBUILDDATA_HPP
#define NON_GRAVITAR_SNIPERENEMYBUILDDATA_HPP

#include "BasicEnemyBuildData.hpp"
#include "SniperEnemyHead.hpp"

class SniperEnemyBuildData : public BasicEnemyBuildData {
public:
    EnemyHead *new_head_logic() override {
        return new SniperEnemyHead(this, this->head_load_paths());
    }


    EnemyOffsets get_offsets() override {
        EnemyOffsets enemy_offsets;
        enemy_offsets.head_offset =                     sge::Vec2<float>(0,1.25);
        enemy_offsets.cannon_offset =                   sge::Vec2<float>(0,0);
        enemy_offsets.shooting_offset =                 sge::Vec2<float>(0,1);
        return enemy_offsets;
    }
};
#endif //NON_GRAVITAR_SNIPERENEMYBUILDDATA_HPP
