#include <SGE/components/graphics/ui/UI.hpp>
#include <player/PlayerPersistentData.hpp>
#include <noise-generation/Perlin.hpp>
#include "PlayerEngine.hpp"

#define NG_ENGINE_NOISE_MAP_SIZE                100
#define NG_ENGINE_NOISE_MAP_CIRCLING_PERIOD     4.f
#define NG_ENGINE_NOISE_MAP_CIRCLING_SPEED      M_PI*2/NG_ENGINE_NOISE_MAP_CIRCLING_PERIOD
#define NG_ENGINE_NOISE_MIN_MULTIPLIER          0.6

#define NG_ENGINE_WIDTH                         0.5
#define NG_ENGINE_TRAIL_CENTRAL_ALPHA           50
#define NG_ENGINE_TRAIL_LATERAL_ALPHA           0.7

std::string PlayerEngine::get_logic_id() {
    return std::string("PlayerEngine");
}

PlayerEngine::PlayerEngine(Rigidbody_H rigidbody, PlayerPersistentData* player_persistent_data)
: noise_map(NG_ENGINE_NOISE_MAP_SIZE, NG_ENGINE_NOISE_MAP_SIZE, 0) {
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

    engine_trail->append_local_point(sge::Vec2<float>(-NG_ENGINE_WIDTH, -0.7));
    engine_trail->append_local_point(sge::Vec2<float>(0, -0.2));
    engine_trail->append_local_point(sge::Vec2<float>(NG_ENGINE_WIDTH, -0.7));
    engine_trail->append_local_point(sge::Vec2<float>(0, -42));

    engine_trail->set_active(false);
    engine_trail->set_layer("engine-trail");

    //engine_trail->set_color(PLAYER_PALETTE.lighter);
    engine_trail->set_vertex_alpha(3, 0);
    engine_trail->set_vertex_alpha(0, (int)NG_ENGINE_TRAIL_CENTRAL_ALPHA*NG_ENGINE_TRAIL_LATERAL_ALPHA);
    engine_trail->set_vertex_alpha(2, (int)NG_ENGINE_TRAIL_CENTRAL_ALPHA*NG_ENGINE_TRAIL_LATERAL_ALPHA);
    engine_trail->set_vertex_alpha(1, NG_ENGINE_TRAIL_CENTRAL_ALPHA);


    // Generate a Perlin NoiseMap for the trail animation
    Perlin surface_perlin(NG_ENGINE_NOISE_MAP_SIZE/6);
    surface_perlin.simple_setup(3,0.6,2);
    surface_perlin.fill_noise_map(noise_map, true);

    noise_map.normalize(NG_ENGINE_NOISE_MIN_MULTIPLIER, 1);

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
    noise_circling_angle += env()->delta_time() * NG_ENGINE_NOISE_MAP_CIRCLING_SPEED;
    if (noise_circling_angle>2*M_PI) noise_circling_angle -= 2 * M_PI;
    auto noise_multiplier = noise_map[(int)(std::cos(noise_circling_angle)*(NG_ENGINE_NOISE_MAP_SIZE/2.f-1) + NG_ENGINE_NOISE_MAP_SIZE/2.f)]
                                     [(int)(std::sin(noise_circling_angle)*(NG_ENGINE_NOISE_MAP_SIZE/2.f-1) + NG_ENGINE_NOISE_MAP_SIZE/2.f)];
    if (engine_trail->is_active()) {
        engine_trail->set_vertex_position(3, 0, -last_thrust_amount*TRAIL_LENGHT_MULTIPLIER*noise_multiplier);
    }
}
