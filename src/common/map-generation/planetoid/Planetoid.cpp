#include "Enemy.hpp"
#include "Crate.hpp"
#include "Planetoid.hpp"


void Planetoid::on_start() {

    enemy_destroyed_ev_handler = [&]() {
        decrease_enemy_counter();
    };

    // APPEAREANCE
    // Main body
    auto main_body = scene()->spawn_gameobject("Main Body");
    main_body->transform()->set_parent(gameobject()->transform());
    auto body_vert_array = main_body->add_component<sge::cmp::VertArray>("VertArray");

    assemble_vert_array(body_vert_array, *planetoid_data->main_fill_square_grid);
    body_vert_array->set_color(planetoid_data->map_gen_info.palette.primary);

    // Secondary fill
    auto secondary_fill = scene()->spawn_gameobject("Secondary Fill");
    secondary_fill->transform()->set_parent(main_body->transform());
    auto secondary_fill_vert_array = secondary_fill->add_component<sge::cmp::VertArray>("VertArray");
    assemble_vert_array(secondary_fill_vert_array, *planetoid_data->secondary_fill_square_grid);
    secondary_fill_vert_array->set_color(planetoid_data->map_gen_info.palette.dark);


    //PHYSICS
    auto rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    rigidbody->set_body_type(b2BodyType::b2_staticBody);

    // Build a chain collider child for every separate wall of the planetoid
    for (int i = 0; i < planetoid_data->main_fill_square_grid->get_paths().size(); ++i) {
        auto wall_go = scene()->spawn_gameobject("Wall " + std::to_string(i));
        wall_go->transform()->set_parent(main_body->transform());
        auto wall_collider = wall_go->add_component<sge::cmp::Collider>("Collider");
        wall_collider->set_as_chain(planetoid_data->main_fill_square_grid->get_paths()[i]);
        wall_collider->set_collision_category("Static Wall");
    }

    // Enemies
    enemy_counter = 0;
    for(EnemyPersistentData* enemy_to_spawn : planetoid_data->map_gen_info.enemies_persistent_data_vec) {
        if (!enemy_to_spawn->destroyed) {
            enemy_counter++;
            enemy_to_spawn->destroy_event += enemy_destroyed_ev_handler;
            auto new_enemy = scene()->spawn_gameobject("Enemy " + std::to_string(enemy_counter));
            new_enemy->transform()->set_local_position(enemy_to_spawn->anchor_position);
            new_enemy->transform()->set_local_rotation(enemy_to_spawn->angle+M_PI_2);
            new_enemy->logichub()->attach_logic(new Enemy(enemy_to_spawn, player_persistent_data));
        }
    }

    // Crates
    int crate_counter = 1;
    for (CratePersistentData *crate_persistent_data : planetoid_data->map_gen_info.crates_persistent_data_vec) {
        if (!crate_persistent_data->destroyed) {
            auto new_crate_go = scene()->spawn_gameobject("Crate " + std::to_string(crate_counter));
            new_crate_go->transform()->set_local_position(crate_persistent_data->position);
            new_crate_go->logichub()->attach_logic(new Crate(crate_persistent_data));
            crate_counter++;
        }
    }
 }

std::string Planetoid::get_logic_id() {
        return std::string("Planetoid");
}

void Planetoid::assemble_vert_array(VertArray_H recipient, const MarchingMap &marching_map, sf::Color color) {
    recipient->set_primitive(sf::PrimitiveType::Triangles);
    for (int k = 0; k < marching_map.width; ++k) {
        for (int i = 0; i < marching_map.height; ++i) {
            for (auto point : marching_map.get_square(k,i).get_fill_triangles()){
                recipient->append_local_point(point, color);
            }
        }
    }
}

void Planetoid::assemble_vert_array(sf::VertexArray& recipient, const MarchingMap &marching_map, sf::Color color) {
    for (int k = 0; k < marching_map.width; ++k) {
        for (int i = 0; i < marching_map.height; ++i) {
            for (auto point : marching_map.get_square(k,i).get_fill_triangles()){
                recipient.append(sf::Vertex(sf::Vector2f(point.x, -point.y), color));
            }
        }
    }
}

const PlanetoidPersistentData *Planetoid::get_planetoid_persistent_data() const {
    return planetoid_data;
}


void Planetoid::decrease_enemy_counter() {
    enemy_counter--;
    if (enemy_counter<=0) {
        planetoid_destroyed_event();
        player_persistent_data->bonus_score.set(player_persistent_data->bonus_score.value() +
                                                planetoid_data->map_gen_info.size * planetoid_data->map_gen_info.size *
                                                planetoid_data->map_gen_info.difficulty_factor / 10);
        planetoid_data->completed = true;
    }
}

void Planetoid::on_scene_destruction() {
    for(EnemyPersistentData* enemy_to_spawn : planetoid_data->map_gen_info.enemies_persistent_data_vec) {
        enemy_to_spawn->destroy_event -= enemy_destroyed_ev_handler;
    }
}

