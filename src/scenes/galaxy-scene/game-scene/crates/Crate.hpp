#ifndef NON_GRAVITAR_CRATE_HPP
#define NON_GRAVITAR_CRATE_HPP


#include <utility-logic/PhysicsObject.hpp>
#include <map-generation/generator/CratePersistentData.hpp>
#include "BreakTrigger.hpp"

#define NG_CRATE_SCALE 0.5
#define NG_CRATE_RESTITUTION 0.8
#define NG_CRATE_ROTATION_SPEED 1
#define NG_CRATE_DISTANCE_FROM_EDGES 1.2
#define NG_CRATE_FADE_DURATION 0.15


class Crate  : public PhysicsObject {
public:
    explicit Crate(CratePersistentData* crate_persistent_data);

    std::string get_logic_id() override;

    void on_start() override;

    void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) override;

    void on_destruction() override;

protected:
    CratePersistentData* crate_persistent_data;
    Rigidbody_H m_rigidbody;
};


#endif //NON_GRAVITAR_CRATE_HPP
