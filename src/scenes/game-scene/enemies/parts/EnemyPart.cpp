#include <BreakTrigger.hpp>
#include <BreakGenerator.hpp>
#include "EnemyPart.hpp"


void EnemyPart::on_start() {
    PhysicsObject::on_start();
    gameobject()->logichub()->attach_logic(break_generator_l);
    gameobject()->logichub()->attach_logic(break_trigger_l);
}

EnemyPart::EnemyPart(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data)
: PhysicsObject(my_breakable_geom_data){
    this->whole_data = whole_data;
    break_generator_l = new BreakGenerator(my_breakable_geom_data.get_max_stuck_pieces_on_break());
    break_trigger_l =new BreakTrigger(10);
}


