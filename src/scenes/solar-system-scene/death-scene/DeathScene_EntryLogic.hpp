#ifndef NON_GRAVITAR_DEATHSCENE_ENTRYLOGIC_HPP
#define NON_GRAVITAR_DEATHSCENE_ENTRYLOGIC_HPP


#include "TextMenu.hpp"


class DeathScene_EntryLogic : public TextMenu {
public:
    DeathScene_EntryLogic(PlayerPersistentData *player_persistent_data);
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    PlayerPersistentData *player_persistent_data;

};


#endif //NON_GRAVITAR_DEATHSCENE_ENTRYLOGIC_HPP
