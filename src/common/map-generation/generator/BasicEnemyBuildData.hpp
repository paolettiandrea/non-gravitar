#ifndef NON_GRAVITAR_BASICENEMYBUILDDATA_HPP
#define NON_GRAVITAR_BASICENEMYBUILDDATA_HPP

#include <SGE/logic/Logic.hpp>
#include <enemies/BasicEnemy.hpp>
#include "EnemyBuildData.hpp"

class BasicEnemyBuildData : public EnemyBuildData {
    float space_needed_on_edge() override {
        return 0.6;
    }

public:
    sge::Logic *get_entry_logic() override {
        return new BasicEnemy();
    }

};
#endif //NON_GRAVITAR_BASICENEMYBUILDDATA_HPP
