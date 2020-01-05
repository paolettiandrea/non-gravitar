#ifndef NON_GRAVITAR_BASICENEMYBUILDDATA_HPP
#define NON_GRAVITAR_BASICENEMYBUILDDATA_HPP

#include <SGE/logic/Logic.hpp>
#include <enemies/Enemy.hpp>
#include "EnemyPersistentData.hpp"

class BasicEnemyBuildData : public EnemyPersistentData {
    float space_needed_on_edge() override {
        return 0.6;
    }

public:

    BreakableObject_ConstructionData base_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic_enemy__base", 3);
    }

    BreakableObject_ConstructionData head_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic_enemy__head", 3);
    }

    BreakableObject_ConstructionData cannon_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic_enemy__cannon", 3);
    }

    BreakableObject_ConstructionData bullet_load_paths() override {
        return BreakableObject_ConstructionData("./res/models/enemies/basic_enemy__bullet", 3);
    }

    sf::Color get_minimap_pin_color() override {
        return sf::Color(200, 30, 30);
    }

    float get_minimap_pin_size() override {
        return 1;
    }

    sge::Vec2<float> head_offset() override {
        return sge::Vec2<float>(0, 1);
    }

};
#endif //NON_GRAVITAR_BASICENEMYBUILDDATA_HPP
