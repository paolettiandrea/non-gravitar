#ifndef NON_GRAVITAR_PLANETOID_HPP
#define NON_GRAVITAR_PLANETOID_HPP

#include <SGE/components/graphics/VertArray.hpp>
#include "SGE/components/physics/Rigidbody.hpp"
#include "SGE/components/physics/Collider.hpp"
#include "SGE/logic/Logic.hpp"
#include "PlanetoidPersistentData.hpp"

class Planetoid : public sge::Logic {
public:
    explicit Planetoid(const PlanetoidPersistentData& planetoid_data, PlayerPersistentData* player_persistent_data) {
        this->planetoid_data = &planetoid_data;
        this->player_persistent_data = player_persistent_data;
    }

    std::string get_logic_id() override;

    void on_start() override;

    static void assemble_vert_array(VertArray_H recipient, const MarchingMap& marching_map, sf::Color = sf::Color::White);
    static void assemble_vert_array(sf::VertexArray& recipient, const MarchingMap &marching_map, sf::Color = sf::Color::White);

    utils::event::Event planetoid_destroyed_event;

    int get_enemy_counter() { return enemy_counter; };
private:

    const PlanetoidPersistentData* planetoid_data;
    PlayerPersistentData *player_persistent_data;

    int enemy_counter = 0;

    utils::event::EventHandler enemy_destroyed_ev_handler;
public:
    const PlanetoidPersistentData *get_planetoid_persistent_data() const;

    void decrease_enemy_counter();

    void on_scene_destruction() override;


};


#endif //NON_GRAVITAR_PLANETOID_HPP
