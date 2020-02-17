#include "Laser.hpp"

std::string Laser::get_logic_id() {
    return std::string("Laser");
}

Laser::Laser(const LaserBuildData& data)
: ray_cast_handler(data.filter, data.ingore_rb, data.starting_pos, data.ending_pos)
, width_animation (new LinearInterpolator(), 0, data.width, data.fade_in_duration){
    this->laser_total_duration = data.duration;
    this->data = data;

}

void Laser::on_update() {
    if (width_animation.is_active()) {
        float new_width = width_animation.step(env()->delta_time());
        set_width(new_width);
    }

    ray_cast_counter += env()->fixed_delta_time();
    total_counter += env()->fixed_delta_time();

    if (total_counter > laser_total_duration) {
        gameobject()->doom();
        return;
    } else {
        if (ray_cast_counter >= NG_LASER_RAY_CAST_PERIOD) {
            ray_cast_counter -= NG_LASER_RAY_CAST_PERIOD;
            scene()->raycast(&ray_cast_handler);
            vert_array->set_vertex_position(2, ray_cast_handler.get_output().point - width_lateral_offset);
            vert_array->set_vertex_position(3, ray_cast_handler.get_output().point + width_lateral_offset);
        }
    }
}

void Laser::on_start() {
    vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    vert_array->set_primitive(sf::PrimitiveType::Quads);
    vert_array->append_local_point(ray_cast_handler.get_point_a());
    vert_array->append_local_point(ray_cast_handler.get_point_a());
    vert_array->append_local_point(ray_cast_handler.get_point_b());
    vert_array->append_local_point(ray_cast_handler.get_point_b());
    vert_array->set_color(data.laser_color);
    vert_array->set_layer("laser");

    width_animation.start();
}

void Laser::set_width(float new_width) {
    if (new_width != displayed_width) {

        width_lateral_offset = (ray_cast_handler.get_point_a() - ray_cast_handler.get_point_b()).set_magnitude(new_width/2.0);
        width_lateral_offset = sge::Vec2<float>::rotate(width_lateral_offset, M_PI_2);
        vert_array->set_vertex_position(0, ray_cast_handler.get_point_a() + width_lateral_offset);
        vert_array->set_vertex_position(1, ray_cast_handler.get_point_a() - width_lateral_offset);
        vert_array->set_vertex_position(2, ray_cast_handler.get_output().point - width_lateral_offset);
        vert_array->set_vertex_position(3, ray_cast_handler.get_output().point + width_lateral_offset);
        displayed_width = new_width;
    }
}
