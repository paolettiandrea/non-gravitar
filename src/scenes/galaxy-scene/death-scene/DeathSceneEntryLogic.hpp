#ifndef NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP
#define NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP


#include <SGE/logic/Logic.hpp>

#define NG_MENU_FONT "ARCADE_R"

class DeathSceneEntryLogic : public sge::Logic {
public:
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;
};


#endif //NON_GRAVITAR_DEATHSCENEENTRYLOGIC_HPP
