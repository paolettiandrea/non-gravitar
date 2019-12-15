#include <enemies/Enemy.hpp>
#include "Planetoid.hpp"


void Planetoid::on_start() {

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
    for(EnemyPersistentData* enemy_to_spawn : planetoid_data->map_gen_info.enemies_build_data) {
        auto new_enemy = scene()->spawn_gameobject("Enemy");
        new_enemy->transform()->set_local_position(enemy_to_spawn->anchor_position);
        new_enemy->transform()->set_local_rotation(enemy_to_spawn->angle+M_PI_2);
        new_enemy->logichub()->attach_logic(new Enemy(enemy_to_spawn));
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
    recipient.setPrimitiveType(sf::PrimitiveType::Triangles);
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

