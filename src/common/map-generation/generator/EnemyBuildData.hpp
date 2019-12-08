#ifndef NON_GRAVITAR_ENEMYBUILDDATA_HPP
#define NON_GRAVITAR_ENEMYBUILDDATA_HPP

#include <PhysicsObject.hpp>
#include "SGE/Vec2.hpp"
#include "SGE/logic/Logic.hpp"
class EnemyBuildData {
public:
    virtual ~EnemyBuildData() {
    }
    virtual float space_needed_on_edge() = 0;

    virtual BreakableObject_ConstructionData base_load_paths() = 0;
    virtual BreakableObject_ConstructionData head_load_paths() = 0;
    virtual BreakableObject_ConstructionData cannon_load_paths() = 0;
    virtual BreakableObject_ConstructionData bullet_load_paths() = 0;

    // structural
    virtual sge::Vec2<float> head_offset() { return sge::Vec2<float>(0,0);};

    sge::Vec2<float> anchor_position;
    float angle;
};
#endif //NON_GRAVITAR_ENEMYBUILDDATA_HPP
