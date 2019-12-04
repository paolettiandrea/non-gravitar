#ifndef NON_GRAVITAR_BIGENEMY_HPP
#define NON_GRAVITAR_BIGENEMY_HPP

#include "Enemy.hpp"

class BigEnemy : public Enemy {
public:
    std::string get_logic_id() override;

    void on_start() override;
};


#endif //NON_GRAVITAR_BIGENEMY_HPP
