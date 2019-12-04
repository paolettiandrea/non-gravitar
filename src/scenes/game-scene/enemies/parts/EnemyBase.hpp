#ifndef NON_GRAVITAR_ENEMYBASE_HPP
#define NON_GRAVITAR_ENEMYBASE_HPP


#include <SGE/logic/Logic.hpp>
#include "EnemyPart.hpp"

class EnemyBase : public EnemyPart {
public:
    EnemyBase(const std::string &mesh_file_path, const std::string &collider_file_path);

    std::string get_logic_id() override;

    void on_start() override;


};


#endif //NON_GRAVITAR_ENEMYBASE_HPP
