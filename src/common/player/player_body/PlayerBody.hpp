#ifndef NON_GRAVITAR_PLAYERBODY_HPP
#define NON_GRAVITAR_PLAYERBODY_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include "PlayerEngine.hpp"
#include "PlayerPersistentData.hpp"


class PlayerBody : public sge::Logic {
public:
    PlayerBody(PlayerPersistentData *player_persistent_data);
    std::string get_logic_id() override;


    void on_start() override;

    void on_update() override;

    void on_fixed_update() override;

private:
    VertArray_H m_vert_array;
    Collider_H m_collider;

    PlayerPersistentData *player_persistent_data;
};


#endif //NON_GRAVITAR_PLAYERBODY_HPP
