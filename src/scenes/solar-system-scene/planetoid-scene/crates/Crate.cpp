#include "Crate.hpp"
#include "COLORS.hpp"


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


    auto background_go = scene()->spawn_gameobject("Background");
    background_go->transform()->set_parent(gameobject()->transform());
    auto background_vertarray = background_go->add_component<sge::cmp::VertArray>("VertArray");
    background_vertarray->import_smesh("./res/models/crates/crate__background.smesh");

    vertarray()->set_color(crate_persistent_data->get_overlay_color());
    vertarray()->set_layer("crate-overlay");
    background_vertarray->set_color(NG_CRATE_BACKGROUND_COLOR);
    background_vertarray->set_layer("crate-background");

    if (!crate_persistent_data->get_content_smesh_path().empty()) {
        auto content_go = scene()->spawn_gameobject("Crate Content");
        content_go->transform()->set_parent(gameobject()->transform());
        content_go->transform()->set_local_scale(crate_persistent_data->get_content_logo_scale());
        auto content_vertarray = content_go->add_component<sge::cmp::VertArray>("VertArray");
        content_vertarray->import_smesh(crate_persistent_data->get_content_smesh_path());
        content_vertarray->set_layer("crate-overlay");
        content_vertarray->set_color(crate_persistent_data->get_overlay_color());
    }
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

