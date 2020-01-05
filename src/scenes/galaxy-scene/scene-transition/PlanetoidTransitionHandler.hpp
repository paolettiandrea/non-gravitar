#ifndef NON_GRAVITAR_PLANETOIDTRANSITIONHANDLER_HPP
#define NON_GRAVITAR_PLANETOIDTRANSITIONHANDLER_HPP

#include "SceneTransitionHandler.hpp"

class PlanetoidTransitionHandler : public SceneTransitionHandler {
public:
    PlanetoidTransitionHandler(SceneTransitionHandler *parent_transition_handler);

    std::string get_logic_id() override;
};


#endif //NON_GRAVITAR_PLANETOIDTRANSITIONHANDLER_HPP
