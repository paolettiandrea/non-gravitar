#ifndef NON_GRAVITAR_PLANETOIDSCENE_ENTRYLOGIC_HPP
#define NON_GRAVITAR_PLANETOIDSCENE_ENTRYLOGIC_HPP

#include <PlanetoidPersistentData.hpp>
#include "SGE/logic/Logic.hpp"

#include "Player.hpp"

#include "MiniaturePlanetoid.hpp"
#include <PlanetoidTransitionHandler.hpp>


#define NG_PLANETOID_SCENE_SPAWN_DISTANCE 20

class PlanetoidScene_EntryLogic : public sge::Logic {
public:
    PlanetoidScene_EntryLogic(PlanetoidPersistentData* planetoid_persistent_data, MiniaturePlanetoid* base_miniature, PlayerPersistentData* player_persistent_data, SceneTransitionHandler* parent_transition_handler);
    std::string get_logic_id() override;

    void on_start() override;

private:
    PlanetoidPersistentData *planetoid_persistent_data;
    MiniaturePlanetoid *base_miniature;
    PlayerPersistentData *player_persistent_data;
    SceneTransitionHandler* parent_transition_handler;

};


#endif //NON_GRAVITAR_PLANETOIDSCENE_ENTRYLOGIC_HPP
