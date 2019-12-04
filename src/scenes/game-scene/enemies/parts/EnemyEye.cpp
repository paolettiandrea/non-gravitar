#include <SGE/utils/interpolation/Interpolator.hpp>
#include <enemies/breakable/BreakGenerator.hpp>
#include "EnemyEye.hpp"

std::string EnemyEye::get_logic_id() {
    return std::string("EnemyEye");
}

EnemyEye::EnemyEye() : eye_wideness_animation(new LinearInterpolator(), SGE_ENEMY_EYE_CLOSED_RADIUS, SGE_ENEMY_EYE_OPEN_RADIUS, 0.15) {

}

void EnemyEye::on_start() {

    m_vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    m_vert_array->set_primitive(sf::PrimitiveType::Triangles);

    for (int i = 0; i < 6; ++i) {
        m_vert_array->append_local_point(sge::Vec2<float>(0, 0));
    }
    m_vert_array->set_color(SGE_ENEMY_EYE_COLOR);

    gameobject()->logichub()->attach_logic(new BreakGenerator(2));

    update_vert_array(SGE_ENEMY_EYE_CLOSED_RADIUS);
}

void EnemyEye::on_update() {
    Logic::on_update();

    float width = eye_wideness_animation.step(env()->delta_time());

    if (width != last_displayed_width) {
        update_vert_array(width);
        last_displayed_width = width;
    }
}

void EnemyEye::update_vert_array(float width) {

    m_vert_array->set_vertex_position(0, 0, width);
    m_vert_array->set_vertex_position(1, -width, 0);
    m_vert_array->set_vertex_position(2, 0, -width);
    m_vert_array->set_vertex_position(3, 0, -width);
    m_vert_array->set_vertex_position(4, width, 0);
    m_vert_array->set_vertex_position(5, 0, width);

}

void EnemyEye::open_eye() {
    eye_wideness_animation.set_from_val(eye_wideness_animation.get_val());
    eye_wideness_animation.set_to_val(SGE_ENEMY_EYE_OPEN_RADIUS);
    eye_wideness_animation.start(true);
}

void EnemyEye::close_eye() {
    eye_wideness_animation.set_from_val(eye_wideness_animation.get_val());
    eye_wideness_animation.set_to_val(SGE_ENEMY_EYE_CLOSED_RADIUS);
    eye_wideness_animation.start(true);
}


