#ifndef NON_GRAVITAR_BULLET_HPP
#define NON_GRAVITAR_BULLET_HPP


#include <SGE/logic/Logic.hpp>
#include <PhysicsObject.hpp>
#include "BreakTrigger.hpp"

class Bullet : public PhysicsObject {
public:
    explicit Bullet (const PhysicsObject_ConstructionData& cd);
    std::string get_logic_id() override;

    void on_start() override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

    void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) override;

    [[nodiscard]] Rigidbody_H get_ignored_body() const;

    void set_ignore_body(Rigidbody_H m_ignore_body);

private:
    Rigidbody_H m_ignore_body;

    BreakTrigger *break_trigger;


};


#endif //NON_GRAVITAR_BULLET_HPP
