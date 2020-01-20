#ifndef NON_GRAVITAR_PLAYERCANNON_HPP
#define NON_GRAVITAR_PLAYERCANNON_HPP


#include <Cannon.hpp>
#include <SGE/components/graphics/ui/blocks/UIBar.hpp>
#include <SGE/components/graphics/ui/UI.hpp>


#define NG_PLAYER_CANNON_DEFAULT_STAMINA            100
#define NG_PLAYER_CANNON_STAMINA_REGEN_PER_SEC      20
#define NG_PLAYER_CANNON_STAMINA_COST_PER_SHOT      20
#define NG_PLAYER_CANNON_MIN_SHOT_FREQUENCY         0.25

class PlayerCannon : public Cannon {
public:
    PlayerCannon(float shooting_velocity, const Rigidbody_H &shooter_rigidbody);

    void on_start() override;

    void on_fixed_update() override;

    void shoot(Bullet *bullet_logic) override;


    bool is_ready_to_shoot();

private:
    UI_H m_ui_component;
    sge::UIBar *stamina_bar;

    float max_stamina = NG_PLAYER_CANNON_DEFAULT_STAMINA;
    float stamina = NG_PLAYER_CANNON_DEFAULT_STAMINA;

    std::chrono::time_point<std::chrono::steady_clock> last_shot_time;
};


#endif //NON_GRAVITAR_PLAYERCANNON_HPP
