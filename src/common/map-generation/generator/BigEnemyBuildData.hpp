#ifndef NON_GRAVITAR_BIGENEMYBUILDDATA_HPP
#define NON_GRAVITAR_BIGENEMYBUILDDATA_HPP

#include <BigEnemy.hpp>
#include "EnemyBuildData.hpp"

class BigEnemyBuildData : public EnemyBuildData {
    float space_needed_on_edge() override {
        return 1.8;
    }

public:
    sge::Logic *get_entry_logic() override {
        return new BigEnemy(); // FIXME
    }
};
#endif //NON_GRAVITAR_BIGENEMYBUILDDATA_HPP
