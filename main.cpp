#include <iostream>

#include "SGE/engine/Engine.hpp"
#include "EntryLogic.hpp"

int main() {

    // Build the engine
    sge::cd::Engine_ConstructionData engine_cd;

    // Render layers setup
    engine_cd.window.layers.emplace_back("planetoid-secondary");
    engine_cd.window.layers.emplace_back("planetoid-walls");
    engine_cd.window.layers.emplace_back("enemy0");
    engine_cd.window.layers.emplace_back("enemy1");
    engine_cd.window.layers.emplace_back("enemy2");

    sge::Engine engine(engine_cd);



    // Initialize the engine with an entry scene
    auto entry_logic = new EntryLogic;
    sge::cd::SceneConstructionData scene_cd("Entry Scene", entry_logic);
    scene_cd.camera_vertical_zoom = 30;
    scene_cd.gravity = sge::Vec2<float>(0,0);

    engine.initialize(scene_cd);

    // Game loop
    while (engine.game_loop()) { }

    return 0;
}