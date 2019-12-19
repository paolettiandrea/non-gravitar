#ifndef NON_GRAVITAR_CRATEPERSISTENTDATA_HPP
#define NON_GRAVITAR_CRATEPERSISTENTDATA_HPP

#include <SGE/Vec2.hpp>
#include <utility-logic/PhysicsObject.hpp>
#include "Player.hpp"

struct CratePersistentData {

    sge::Vec2<float> position;

    bool destroyed = false;

    virtual BreakableObject_ConstructionData get_base_construction_data() {
        return BreakableObject_ConstructionData("./res/models/crates/crate__base", 1);
    }

    virtual void apply_effect_on_player(Player* player_logic) = 0;

};

#endif //NON_GRAVITAR_CRATEPERSISTENTDATA_HPP
