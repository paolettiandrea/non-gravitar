#include "PlayerCannon.hpp"

PlayerCannon::PlayerCannon(float shooting_velocity, const Rigidbody_H &shooter_rigidbody, PlayerPersistentData *data)
: Cannon(shooting_velocity, shooter_rigidbody) {
    this->player_persistent_data = data;
}




void PlayerCannon::on_fixed_update() {

    auto& stamina = player_persistent_data->stamina_amount;
    auto& max_stamina = player_persistent_data->stamina_max;
    if (stamina.value() < max_stamina.value()) {
        stamina.set(stamina.value() + NG_PLAYER_CANNON_STAMINA_REGEN_PER_SEC * env()->fixed_delta_time());
        if (stamina.value() > max_stamina.value()) {
            stamina.set(max_stamina.value());
        }
    }
}

void PlayerCannon::on_start() {
    last_shot_time = std::chrono::steady_clock::now();
}

void PlayerCannon::shoot(Bullet *bullet_logic) {
    Cannon::shoot(bullet_logic);
    last_shot_time = std::chrono::steady_clock::now();
    player_persistent_data->stamina_amount.set(player_persistent_data->stamina_amount.value() - NG_PLAYER_CANNON_STAMINA_COST_PER_SHOT);
}

bool PlayerCannon::is_ready_to_shoot() {
    if (player_persistent_data->stamina_amount.value() > NG_PLAYER_CANNON_STAMINA_COST_PER_SHOT) {
        auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_shot_time).count() / 1000.0;
        if (passed > NG_PLAYER_CANNON_MIN_SHOT_FREQUENCY) return true;
    }
    return false;
}


