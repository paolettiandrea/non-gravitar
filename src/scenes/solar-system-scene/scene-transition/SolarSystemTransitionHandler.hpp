#ifndef NON_GRAVITAR_SOLARSYSTEMTRANSITIONHANDLER_HPP
#define NON_GRAVITAR_SOLARSYSTEMTRANSITIONHANDLER_HPP


#include "SceneTransitionHandler.hpp"

class SolarSystemTransitionHandler : public SceneTransitionHandler {
public:
    explicit SolarSystemTransitionHandler(Player *player_l);

    virtual ~SolarSystemTransitionHandler();

    void launch_planetoid_scene(MiniaturePlanetoid *base_miniature);

    std::string get_logic_id() override;

protected:


private:
    Player* player_logic;
    utils::event::EventHandler* launch_planetoid_callback = nullptr;


};


#endif //NON_GRAVITAR_SOLARSYSTEMTRANSITIONHANDLER_HPP
