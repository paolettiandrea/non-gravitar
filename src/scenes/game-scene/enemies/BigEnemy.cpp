#include <SGE/components/graphics/VertArray.hpp>
#include "BigEnemy.hpp"

std::string BigEnemy::get_logic_id() {
    return std::string("BigEnemy");
}

void BigEnemy::on_start() {
    Enemy::on_start();
    auto vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    vert_array->import_smesh("./res/models/enemies/big_enemy__body.smesh");
    vert_array->set_color(sf::Color::Yellow);
}
