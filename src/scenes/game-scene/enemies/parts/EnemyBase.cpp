#include <enemies/breakable/Breakable.hpp>
#include <BreakGenerator.hpp>
#include <enemies/breakable/BreakTrigger.hpp>
#include "EnemyBase.hpp"

std::string EnemyBase::get_logic_id() {
    return std::string("EnemyBase");
}

EnemyBase::EnemyBase(const std::string &mesh_file_path, const std::string &collider_file_path)
: EnemyPart(mesh_file_path, collider_file_path) {

}

void EnemyBase::on_start() {
    EnemyPart::on_start();

}


