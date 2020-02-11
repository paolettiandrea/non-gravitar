#ifndef NON_GRAVITAR_SOLARSYSTEMSCENE_ENTRYLOGIC_HPP
#define NON_GRAVITAR_SOLARSYSTEMSCENE_ENTRYLOGIC_HPP


#include <SGE/logic/Logic.hpp>
#include "PlayerPersistentData.hpp"
#include "GAME.hpp"
#include "PlanetoidManager.hpp"



class SolarSystemScene_EntryLogic : public sge::Logic {
public:
    explicit SolarSystemScene_EntryLogic(PlayerPersistentData *player_persistent_data);
    void on_start() override;

    std::string get_logic_id() override;

    void on_scene_resume() override;

private:
    PlayerPersistentData *player_persistent_data;
    PlanetoidManager *planetoid_manager_l;

    utils::event::EventHandler on_completion_key_ev_handler;
    utils::event::EventHandler on_completion_animation_ended_ev_handler;

    void spawn_planets(const SolarSystem_ConstructionData& solar_sys_construction_data, const std::vector<PlanetoidPersistentData*>& data_vec);

};

#endif //NON_GRAVITAR_SOLARSYSTEMSCENE_ENTRYLOGIC_HPP
