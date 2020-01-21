#ifndef NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP
#define NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP


#include "TextMenu.hpp"


class DeathSceneEntryLogic : public TextMenu {
public:
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

};


#endif //NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP
