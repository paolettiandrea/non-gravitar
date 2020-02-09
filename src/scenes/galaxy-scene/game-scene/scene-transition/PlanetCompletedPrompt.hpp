#ifndef NON_GRAVITAR_PLANETCOMPLETEDPROMPT_HPP
#define NON_GRAVITAR_PLANETCOMPLETEDPROMPT_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include <map-generation/planetoid/Planetoid.hpp>

class PlanetCompletedPrompt : public sge::Logic {
public:
    explicit PlanetCompletedPrompt(Planetoid *planetoid, utils::event::EventHandler key_pressed_ev_handler);
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    UI_H ui;
    Planetoid *planetoid;
    utils::event::EventHandler key_pressed_ev_handler;
};


#endif //NON_GRAVITAR_PLANETCOMPLETEDPROMPT_HPP
