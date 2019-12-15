#ifndef NON_GRAVITAR_PLAYER_HPP
#define NON_GRAVITAR_PLAYER_HPP

#include "SGE/logic/Logic.hpp"

#include "SGE/components/graphics/VertArray.hpp"
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include <SGE/components/graphics/ui/blocks/UIBar.hpp>
#include <scaled-planetoid/minimap/MinimapTraced_I.hpp>

#include "PlayerBody.hpp"


class Player : public sge::Logic, public MinimapTraced_I  {
public:
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

    sge::Vec2<float> get_position_relative_to_planetoid() override;

    std::vector<sf::Vertex> get_minimap_model_vertices() override;

private:
    Rigidbody_H m_rigidbody;
    Collider_H m_collider;
    PlayerBody* m_body;
public:
    GameObject_H  get_body_gameobject() const;


};


#endif //NON_GRAVITAR_PLAYER_HPP
