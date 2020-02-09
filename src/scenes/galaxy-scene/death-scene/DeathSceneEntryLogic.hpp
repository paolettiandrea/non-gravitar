#ifndef NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP
#define NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP


#include "TextMenu.hpp"


class DeathSceneEntryLogic : public TextMenu {
public:
    DeathSceneEntryLogic(PlayerPersistentData *player_persistent_data);
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    PlayerPersistentData *player_persistent_data;

};


#endif //NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP
