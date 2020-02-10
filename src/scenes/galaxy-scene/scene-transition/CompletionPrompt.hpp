#ifndef NON_GRAVITAR_COMPLETIONPROMPT_HPP
#define NON_GRAVITAR_COMPLETIONPROMPT_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include <map-generation/planetoid/Planetoid.hpp>

class CompletionPrompt : public sge::Logic {
public:
    explicit CompletionPrompt(utils::event::EventHandler key_pressed_ev_handler, const std::string& prompt_string);
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    UI_H ui;
    utils::event::EventHandler key_pressed_ev_handler;
    std::string prompt_string;
};


#endif //NON_GRAVITAR_COMPLETIONPROMPT_HPP
