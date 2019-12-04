#ifndef NON_GRAVITAR_PLAYERBODY_HPP
#define NON_GRAVITAR_PLAYERBODY_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include "PlayerEngine.hpp"


class PlayerBody : public sge::Logic {
public:
    std::string get_logic_id() override;


    void on_start() override;

    void on_update() override;

    void on_fixed_update() override;

private:
    utils::Handle<sge::cmp::VertArray> m_vert_array;
    utils::Handle<sge::cmp::Collider> m_collider;
};


#endif //NON_GRAVITAR_PLAYERBODY_HPP
