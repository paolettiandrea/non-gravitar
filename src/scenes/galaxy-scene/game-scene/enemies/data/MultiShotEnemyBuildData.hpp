#ifndef NON_GRAVITAR_MULTISHOTENEMYBUILDDATA_HPP
#define NON_GRAVITAR_MULTISHOTENEMYBUILDDATA_HPP


#include <MultiShotEnemyHead.hpp>
#include "BasicEnemyBuildData.hpp"

class MultiShotEnemyBuildData : public BasicEnemyBuildData {
public:
    EnemyHead *new_head_logic(EnemyBuildData *whole_data,
                              const BreakableObject_ConstructionData &my_breakable_geom_data) override {
        return new MultiShotEnemyHead(whole_data, my_breakable_geom_data);
    }


};


#endif //NON_GRAVITAR_MULTISHOTENEMYBUILDDATA_HPP
