#ifndef NON_GRAVITAR_PAUSESCENEENTRYLOGIC_HPP
#define NON_GRAVITAR_PAUSESCENEENTRYLOGIC_HPP


#include "TextMenu.hpp"
#include "COLORS.hpp"


class PauseScene_EntryLogic : public TextMenu {
    std::string get_logic_id() override;

    void on_start() override;
    void on_update() override;

};


#endif //NON_GRAVITAR_PAUSESCENEENTRYLOGIC_HPP
