#ifndef NON_GRAVITAR_GAMESCENEENTRYLOGIC_HPP
#define NON_GRAVITAR_GAMESCENEENTRYLOGIC_HPP


#include <SGE/logic/Logic.hpp>
#include <player/PlayerPersistentData.hpp>

class GameScene_EntryLogic : public sge::Logic {
public:
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    PlayerPersistentData player_persistent_data;
    float difficulty_multiplier = 1.f;
};


#endif //NON_GRAVITAR_GAMESCENEENTRYLOGIC_HPP
