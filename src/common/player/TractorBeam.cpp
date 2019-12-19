#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include "TractorBeam.hpp"
#include "PlayerPersistentData.hpp"

std::string TractorBeam::get_logic_id() {
    return std::string("TractorBeam");
}

void TractorBeam::on_start() {
    auto my_local_pos = gameobject()->transform()->get_local_position();
    auto col = gameobject()->add_component<sge::cmp::Collider>("Collider");
    col->set_sensor(true);

    auto left_dir = sge::Vec2<float>::rotate(sge::Vec2<float>(0,1), NG_TRACTOR_BEAM_ANGLE);
    auto right_dir = sge::Vec2<float>::rotate(sge::Vec2<float>(0,1), -NG_TRACTOR_BEAM_ANGLE);

    sge::Path col_path;
    col_path.append_point((my_local_pos + left_dir) * NG_TRACTOR_BEAM_INITIAL_MASKED_LENGHT);
    col_path.append_point((my_local_pos + right_dir) * NG_TRACTOR_BEAM_INITIAL_MASKED_LENGHT);

    auto angle_step = NG_TRACTOR_BEAM_ANGLE * 2 / NG_TRACTOR_BEAM_NUMBER_OF_SLICES;
    for (int i = 0; i <= NG_TRACTOR_BEAM_NUMBER_OF_SLICES; ++i) {
        auto angle = -NG_TRACTOR_BEAM_ANGLE+angle_step*i;
        sge::Vec2<float> point(std::sin(angle), std::cos(angle));
        col_path.append_point(point*NG_TRACTOR_BEAM_LENGHT);
    }
    col_path.set_closed(true);
    col->set_as_polygon(col_path);

    vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    vert_array->set_primitive(sf::PrimitiveType::Quads);
    vert_array->set_layer("tractor-beam");

    for (int j = 0; j < NG_TRACTOR_BEAM_NUMBER_OF_SLICES; ++j) {
        vert_array->append_local_point(col_path[1]);
        vert_array->append_local_point(col_path[0]);
        vert_array->append_local_point(col_path[2 + j]);
        vert_array->append_local_point(col_path[3 + j]);
    }

    vert_array->set_color(PlayerPersistentData::palette.light);
    vert_array->set_alpha(7);

}

void TractorBeam::on_collision_begin(sge::CollisionInfo &collision_info) {
    if (collision_info.m_its_collider->get_rigidbody()->get_b2_body()->GetType() == b2_dynamicBody) {
        bool found = false;
        for (auto body : colliding_bodies) {
            if (body == collision_info.m_its_collider->get_rigidbody()) { found = true; }
        }
        if (!found) colliding_bodies.push_back(collision_info.m_its_collider->get_rigidbody());
    }
}

void TractorBeam::on_collision_end(sge::CollisionInfo &collision_info) {
    if (collision_info.m_its_collider.is_valid()) {
        if (collision_info.m_its_collider->get_rigidbody()->get_b2_body()->GetType() == b2_dynamicBody) {
            colliding_bodies.remove(collision_info.m_its_collider->get_rigidbody());
        }
    }
}


void TractorBeam::on_fixed_update() {
    if (env()->is_key_down(NG_TRACTOR_BEAM_KEY)) {
        std::list<Rigidbody_H> bodies_to_remove;
        for (auto body : colliding_bodies) {
            if (body.is_valid()) {

                auto dir = (gameobject()->transform()->get_world_position() -
                            body->gameobject()->transform()->get_world_position()).normalize();
                body->apply_force_center(dir * NG_TRACTOR_BEAM_FORCE, true);


                env()->debug_draw_point(body->gameobject()->transform()->get_world_position());
            } else {
                bodies_to_remove.push_back(body);
            }
        }

        for (auto body_to_remove : bodies_to_remove) {
            colliding_bodies.remove(body_to_remove);
        }
    }
}

void TractorBeam::on_update() {
    if (env()->is_key_pressed(NG_TRACTOR_BEAM_KEY)) {
        vert_array->set_active(true);
    }

    if (env()->is_key_released(NG_TRACTOR_BEAM_KEY)) {
        vert_array->set_active(false);
    }
}
