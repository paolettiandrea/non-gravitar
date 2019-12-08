#include <iostream>

#include "SGE/engine/Engine.hpp"
#include "EntryLogic.hpp"

int main() {

    // Build the engine
    sge::cd::Engine_ConstructionData engine_cd;

    // Render layers setup
    engine_cd.window.layers.emplace_back("planetoid-secondary");
    engine_cd.window.layers.emplace_back("planetoid-walls");
    engine_cd.window.layers.emplace_back("enemy_head");
    engine_cd.window.layers.emplace_back("enemy_base");
    engine_cd.window.layers.emplace_back("enemy_cannon");
    engine_cd.window.layers.emplace_back("bullet");

    engine_cd.physics.collision_layer_ids.emplace_back("Default");
    engine_cd.physics.collision_layer_ids.emplace_back("Player");
    engine_cd.physics.collision_layer_ids.emplace_back("Enemy");
    engine_cd.physics.collision_layer_ids.emplace_back("Static Wall");


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