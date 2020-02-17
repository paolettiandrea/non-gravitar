#ifndef NON_GRAVITAR_PLANETOIDTRANSITIONHANDLER_HPP
#define NON_GRAVITAR_PLANETOIDTRANSITIONHANDLER_HPP

#include "SceneTransitionHandler.hpp"

class PlanetoidTransitionHandler : public SceneTransitionHandler {
public:
    PlanetoidTransitionHandler(SceneTransitionHandler *parent_transition_handler, Planetoid* planetoid, MiniaturePlanetoid* miniature_planetoid);

    std::string get_logic_id() override;

    void on_start() override;

    void pop_scene() override;

    const PlanetoidPersistentData* get_planetoid_data() { return planetoid->get_planetoid_persistent_data(); }

private:
    Planetoid* planetoid;

    void build_completed_prompt();

    MiniaturePlanetoid *miniature_planetoid;


};


#endif //NON_GRAVITAR_PLANETOIDTRANSITIONHANDLER_HPP
