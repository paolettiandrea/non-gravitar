#ifndef NON_GRAVITAR_ENEMYBUILDDATA_HPP
#define NON_GRAVITAR_ENEMYBUILDDATA_HPP

#include "SGE/Vec2.hpp"
#include "SGE/logic/Logic.hpp"
class EnemyBuildData {
public:
    virtual ~EnemyBuildData() {
    }
    virtual float space_needed_on_edge() = 0;
    virtual sge::Logic* get_entry_logic() = 0;

    sge::Vec2<float> anchor_position;
    float angle;
};
#endif //NON_GRAVITAR_ENEMYBUILDDATA_HPP
