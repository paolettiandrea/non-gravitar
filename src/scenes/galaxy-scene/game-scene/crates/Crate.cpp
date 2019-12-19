#include <game-scene/breakable/handler/BreakHandler.hpp>
#include <game-scene/breakable/generator/BreakGenerator.hpp>
#include <utility-logic/Fading.hpp>
#include "Crate.hpp"


Crate::Crate(CratePersistentData *crate_persistent_data)
    : PhysicsObject(crate_persistent_data->get_base_construction_data()) {
    this->crate_persistent_data = crate_persistent_data;
}

void Crate::on_start() {
    gameobject()->transform()->set_local_scale(NG_CRATE_SCALE);
    m_rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    PhysicsObject::on_start();

    m_rigidbody->get_b2_body()->SetAngularVelocity(NG_CRATE_ROTATION_SPEED);

    collider()->set_restitution(NG_CRATE_RESTITUTION);
}

std::string Crate::get_logic_id() {
    return std::string("Crate");
}

void Crate::on_destruction() {
    if (!scene()->is_doomed()) {
        crate_persistent_data->destroyed = true;
    }
}

void Crate::pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) {
    Logic::pre_solve(contact, oldManifold, info);
    auto its_go = info.m_its_collider->get_rigidbody()->gameobject();
    if (its_go->logichub()->has_logic("Player")) {
        contact->SetEnabled(false);
        if (!crate_persistent_data->destroyed) {
            collider()->set_collision_category("Fading Fragment");
            gameobject()->logichub()->attach_logic(new Fading(NG_CRATE_FADE_DURATION));
            crate_persistent_data->apply_effect_on_player(its_go->logichub()->get_logic_by_id<Player>("Player"));
            crate_persistent_data->destroyed = true;
        }
    }
}

