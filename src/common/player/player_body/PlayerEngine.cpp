#include <SGE/components/graphics/ui/UI.hpp>
#include <player/PlayerPersistentData.hpp>
#include "PlayerEngine.hpp"

std::string PlayerEngine::get_logic_id() {
    return std::string("PlayerEngine");
}

PlayerEngine::PlayerEngine(Rigidbody_H rigidbody, PlayerPersistentData* player_persistent_data) {
    controlled_rigidbody = rigidbody;
    this->player_persistent_data = player_persistent_data;

}

void PlayerEngine::on_start() {

    INITIAL_THRUST_TARGET = BASE_ACCELERATION * MAX_INITIAL_THRUST_FACTOR;
    INITIAL_FORCE_DELTA = INITIAL_THRUST_TARGET*env()->fixed_delta_time()/THRUST_INCREASE_TIME;
    STABILIZATION_FORCE_DELTA = (BASE_ACCELERATION - INITIAL_THRUST_TARGET) * env()->fixed_delta_time() / THRUST_STABILIZATION_TIME;
    DECREASE_FORCE_DELTA = -BASE_ACCELERATION * env()->fixed_delta_time() / THRUST_DECREASE_TIME;

    engine_trail = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    engine_trail->set_primitive(sf::PrimitiveType::Quads);

    engine_trail->append_local_point(sge::Vec2<float>(-0.5, -1));
    engine_trail->append_local_point(sge::Vec2<float>(0, -0.5));
    engine_trail->append_local_point(sge::Vec2<float>(0.5, -1));
    engine_trail->append_local_point(sge::Vec2<float>(0, -9));

    engine_trail->set_vertex_color(3, sf::Color::Transparent);

    engine_trail->set_active(false);
}

void PlayerEngine::on_fixed_update() {

    if (env()->is_key_pressed(NG_CONTROLS_PLAYER_THRUST_KEY)) {
        if (thrust_status != Increasing) {
            thrust_status = Increasing;
        }
    }

    if (env()->is_key_released(NG_CONTROLS_PLAYER_THRUST_KEY)) {
        thrust_status = Decreasing;
    }

    float thrust_this_fixedupdate = 0;

    // Calculate the thrust to apply this fixedupdate based on the status of the engine
    switch (thrust_status) {
        case Increasing:
            thrust_this_fixedupdate = last_thrust_amount + INITIAL_FORCE_DELTA;
            if (thrust_this_fixedupdate >= INITIAL_THRUST_TARGET) {
                thrust_this_fixedupdate = INITIAL_THRUST_TARGET;
                thrust_status = Stabilizing;
            }
            engine_trail->set_active(true);
            break;

        case Stabilizing:
            thrust_this_fixedupdate = last_thrust_amount + STABILIZATION_FORCE_DELTA;
            if (thrust_this_fixedupdate <= BASE_ACCELERATION) {
                thrust_this_fixedupdate = BASE_ACCELERATION;
                thrust_status = Stable;
            }
            break;

        case Stable:
            thrust_this_fixedupdate = BASE_ACCELERATION;
            break;

        case Decreasing:
            thrust_this_fixedupdate = last_thrust_amount + DECREASE_FORCE_DELTA;
            if (thrust_this_fixedupdate <= 0) {
                thrust_this_fixedupdate = 0;
                thrust_status = Zero;
                engine_trail->set_active(false);
            }
            break;
    }

    // Apply thrust if not null
    if (thrust_this_fixedupdate!=0) {
        auto thrust = controlled_rigidbody->get_b2_body()->GetMass() * thrust_this_fixedupdate;
        auto transformed_dir = sge::Vec2<float>::rotate(sge::Vec2<float>(0,thrust), gameobject()->transform()->get_world_rotation());
        controlled_rigidbody->apply_force_center(transformed_dir, true);

        player_persistent_data->fuel_amount.set(player_persistent_data->fuel_amount.value() - thrust_this_fixedupdate / FUEL_EFFICIENCY_FACTOR);
    }
    last_thrust_amount = thrust_this_fixedupdate;
}

void PlayerEngine::on_update() {
    update_engine_trail_lenght();
}

void PlayerEngine::update_engine_trail_lenght() {
    if (engine_trail->is_active()) {
        engine_trail->set_vertex_position(3, 0, -last_thrust_amount*TRAIL_LENGHT_MULTIPLIER);
    }
}
