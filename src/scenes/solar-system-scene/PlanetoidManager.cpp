#include <SGE/components/physics/Collider.hpp>
#include <random>

#include "BasicEnemyPersistentData.hpp"
#include "FuelCratePersistentData.hpp"
#include "MultiShotEnemyPersistentData.hpp"
#include "SniperEnemyBuildData.hpp"
#include "MaxFuelCratePersistentData.hpp"
#include "ExtraLifeCratePersistentData.hpp"
#include "MaxStaminaCratePersistentData.hpp"
#include "PlanetoidManager.hpp"
#include "Planetoid.hpp"
#include "MapGenInfo.hpp"
#include "GAME.hpp"

std::string PlanetoidManager::get_logic_id() {
    return std::string("PlanetoidManager");
}


PlanetoidManager::~PlanetoidManager() {
    for (int i = 0; i < planetoid_data_vec.size(); ++i) {

        for (int j = 0; j < planetoid_data_vec[i]->map_gen_info.enemies_persistent_data_vec.size(); ++j) {
            delete (planetoid_data_vec[i]->map_gen_info.enemies_persistent_data_vec[j]);
        }

        for (int j = 0; j < planetoid_data_vec[i]->map_gen_info.crates_persistent_data_vec.size(); ++j) {
            delete (planetoid_data_vec[i]->map_gen_info.crates_persistent_data_vec[j]);
        }
        delete (planetoid_data_vec[i]);
    }
}

PlanetoidManager::PlanetoidManager(const SolarSystem_ConstructionData &data) {

    planetoid_data_vec.reserve(data.planetoid_number);
    for (int i = 0; i < data.planetoid_number; ++i) {
        MapGenInfo map_gen_info;

        if (data.planetoid_number > 1) {
            LinearInterpolator interpolator;
            auto t = ((float) i) / (data.planetoid_number-1.0);
            map_gen_info.size = interpolator.interpolate(t, data.min_planetoid_size, data.max_planetoid_size);
            map_gen_info.difficulty_factor = interpolator.interpolate(t, data.min_difficulty_factor, data.max_difficulty_factor);
        } else {
            map_gen_info.size = data.min_planetoid_size;
            map_gen_info.difficulty_factor = data.min_difficulty_factor;
        }


        float enemy_density = NG_GAME_BASE_ENEMY_DENSITY * map_gen_info.difficulty_factor;
        int planetoid_area = map_gen_info.size * map_gen_info.size;
        int enemy_number = planetoid_area * enemy_density;
        if (enemy_number < 1) enemy_number = 1;

        int basic_enemies = enemy_number/4, multi_enemies = enemy_number/4, sniper_enemies = enemy_number/4;
        int compensation = enemy_number - basic_enemies - multi_enemies - sniper_enemies;

        if (map_gen_info.difficulty_factor > 3) {
            sniper_enemies += compensation;
            map_gen_info.palette = PLANETOID_HARD_PALETTE;
        } else {
            if (map_gen_info.difficulty_factor > 2){
                multi_enemies += compensation;
                map_gen_info.palette = PLANETOID_MEDIUM_PALETTE;
            } else { basic_enemies += compensation; }
        }

        for (int j = 0; j < basic_enemies; ++j) {
            map_gen_info.enemies_persistent_data_vec.push_back(new BasicEnemyPersistentData());
        }
        for (int j = 0; j < multi_enemies; ++j) {
            map_gen_info.enemies_persistent_data_vec.push_back(new MultiShotEnemyPersistentData());
        }
        for (int j = 0; j < sniper_enemies; ++j) {
            map_gen_info.enemies_persistent_data_vec.push_back(new SniperEnemyBuildData());
        }


        // CRATES

        float crate_density = NG_GAME_BASE_CRATE_DENSITY / map_gen_info.difficulty_factor;
        int crate_number = planetoid_area * crate_density;
        for (int j = 0; j < crate_number; ++j) {
            map_gen_info.crates_persistent_data_vec.push_back(new FuelCratePersistentData());
        }
        add_special_crates(map_gen_info);

        planetoid_data_vec.push_back(new PlanetoidPersistentData(map_gen_info));
    }

    std::shuffle(planetoid_data_vec.begin(), planetoid_data_vec.end(), std::mt19937(std::random_device()()));
}

const std::vector<PlanetoidPersistentData *> &PlanetoidManager::get_planetoid_data_vec() const {
    return planetoid_data_vec;
}

void PlanetoidManager::add_special_crates(MapGenInfo& map_gen_info) {


    auto actual_1up_chance = NG_GAME_BASE_CRATE_1UP_CHANCE/map_gen_info.difficulty_factor;
    auto actual_maxup_chance = NG_GAME_BASE_CRATE_MAXUP_CHANCE/map_gen_info.difficulty_factor;

    auto r = ((double) rand() / (RAND_MAX));
    if (actual_1up_chance>r) map_gen_info.crates_persistent_data_vec.push_back(new ExtraLifeCratePersistentData());
    r = ((double) rand() / (RAND_MAX));
    if (actual_maxup_chance>r) {
        r = ((double) rand() / (RAND_MAX));
        if (r>=0.5f) map_gen_info.crates_persistent_data_vec.push_back(new MaxFuelCratePersistentData());
        else map_gen_info.crates_persistent_data_vec.push_back(new MaxStaminaCratePersistentData());
    }
}

