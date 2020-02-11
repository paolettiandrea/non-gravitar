#include <iostream>
#include <GameSceneEntryLogic.hpp>

#include "SGE/engine/Engine.hpp"
#include "PlanetoidScene_EntryLogic.hpp"
#include "SolarSystemScene_EntryLogic.hpp"

int main() {

    // Build the engine
    sge::cd::Engine_ConstructionData engine_cd;

    //engine_cd.window.vsync_on = false;

    // Render layers setup
    engine_cd.window.layers.emplace_back("planetoid-secondary");
    engine_cd.window.layers.emplace_back("planetoid-walls");
    engine_cd.window.layers.emplace_back("player");
    engine_cd.window.layers.emplace_back("engine-trail");
    engine_cd.window.layers.emplace_back("tractor-beam");
    engine_cd.window.layers.emplace_back("crate-overlay");
    engine_cd.window.layers.emplace_back("crate-background");
    engine_cd.window.layers.emplace_back("enemy_head");
    engine_cd.window.layers.emplace_back("enemy_base");
    engine_cd.window.layers.emplace_back("enemy_cannon");
    engine_cd.window.layers.emplace_back("bullet");
    engine_cd.window.layers.emplace_back("laser");

    engine_cd.physics.collision_layer_ids.emplace_back("Default");
    engine_cd.physics.collision_layer_ids.emplace_back("Player");
    engine_cd.physics.collision_layer_ids.emplace_back("Enemy");
    engine_cd.physics.collision_layer_ids.emplace_back("Bullet");
    engine_cd.physics.collision_layer_ids.emplace_back("Static Wall");
    engine_cd.physics.collision_layer_ids.emplace_back("Fading Fragment");


    sge::Engine engine(engine_cd);



    // Initialize the engine with an entry scene
    auto entry_logic = new GameScene_EntryLogic();
    sge::cd::SceneConstructionData scene_cd("Entry Scene", entry_logic);
    scene_cd.camera_vertical_zoom = 30;

    engine.initialize(scene_cd);

    // Game loop
    while (engine.game_loop()) { }

    return 0;
}