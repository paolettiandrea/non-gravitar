#include <SGE/components/graphics/VertArray.hpp>
#include <BasicEnemyBuildData.hpp>
#include "PlanetoidManager.hpp"
#include "SGE/components/physics/Collider.hpp"
#include "Planetoid.hpp"
#include "MapGenInfo.hpp"

std::string PlanetoidManager::get_logic_id() {
    return std::string("PlanetoidManager");
}

void PlanetoidManager::on_start() {
    generate_planetoids();
}

void PlanetoidManager::generate_planetoids() {

    MapGenInfo map_gen_info_array[2];

    map_gen_info_array[0].primary_color = sf::Color(40,160,40);
    map_gen_info_array[0].secondary_color = sf::Color(40,120,40);

    map_gen_info_array[1].primary_color = sf::Color(160,60,40);
    map_gen_info_array[1].secondary_color = sf::Color(120,60,40);


    for (int i = 0; i < NON_GRAVITAR_GENERATED_PLANETOIDS; ++i) {

        map_gen_info_array[i].size = 200  + 50*i;


        for (int j = 0; j < 10; ++j) {
            map_gen_info_array[i].enemies_to_spawn.push_back(new BasicEnemyBuildData());
        }



        planetoid_data[i] = new PlanetoidData(map_gen_info_array[i]);
        auto new_planetoid_go = scene()->spawn_gameobject("Planetoid " + std::to_string(i));
        new_planetoid_go->logichub()->attach_logic(new Planetoid(*planetoid_data[i]));
        new_planetoid_go->transform()->set_local_position(300*i, 0);


    }
}

