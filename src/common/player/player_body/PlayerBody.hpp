#ifndef NON_GRAVITAR_PLAYERBODY_HPP
#define NON_GRAVITAR_PLAYERBODY_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include "PlayerEngine.hpp"
#include "PlayerPersistentData.hpp"
#include "CONTROLS.hpp"

#define NG_PLAYER_ROTATION_SPEED        M_PI*3.f          // In radians per sec
#define NG_PLAYER_ROTATION_SHARPNESS    15.f

class PlayerBody : public sge::Logic {
public:
    explicit PlayerBody(PlayerPersistentData *player_persistent_data);

    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    VertArray_H m_vert_array;
    Collider_H m_collider;

    PlayerPersistentData *player_persistent_data;

    float target_rotation_vel = NG_PLAYER_ROTATION_SPEED;
    float current_rotation_vel = 0.f;
};


#endif //NON_GRAVITAR_PLAYERBODY_HPP
