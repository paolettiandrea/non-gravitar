#include "PauseLauncher.hpp"
#include "PauseSceneEntryLogic.hpp"

std::string PauseLauncher::get_logic_id() {
    return std::string("PauseLauncher");
}

void PauseLauncher::on_update() {
    if (env()->is_key_pressed(NG_CONTROLS_PAUSE_KEY)) {
        env()->book_new_scene_push("Pause Menu", new PauseScene_EntryLogic());
    }
}
