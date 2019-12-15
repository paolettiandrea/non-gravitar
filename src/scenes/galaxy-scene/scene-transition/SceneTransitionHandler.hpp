#ifndef NON_GRAVITAR_SCENETRANSITIONHANDLER_HPP
#define NON_GRAVITAR_SCENETRANSITIONHANDLER_HPP


#include <SGE/logic/Logic.hpp>
#include <Player.hpp>
#include <PlanetoidPersistentData.hpp>
#include "MiniaturePlanetoid.hpp"

class SceneTransitionHandler : public sge::Logic {
public:
    explicit SceneTransitionHandler(Player *player_l);

    void launch_planetoid_scene(PlanetoidPersistentData *planetoid_persistent_data, MiniaturePlanetoid *base_miniature);

    std::string get_logic_id() override;


private:
    Player* player_logic;
};


#endif //NON_GRAVITAR_SCENETRANSITIONHANDLER_HPP
