#include <SGE/components/graphics/VertArray.hpp>
#include <BasicEnemyBuildData.hpp>
#include "PlanetoidManager.hpp"
#include "SGE/components/physics/Collider.hpp"
#include "Planetoid.hpp"
#include "MapGenInfo.hpp"

std::string PlanetoidManager::get_logic_id() {
    return std::string("PlanetoidManager");
}


PlanetoidManager::~PlanetoidManager() {
    for (int i = 0; i < planetoid_data_vec.size(); ++i) {
        delete (planetoid_data_vec[i]);
    }
}

PlanetoidManager::PlanetoidManager(const Galaxy_ConstructionData &data) {

    planetoid_data_vec.reserve(data.planetoid_number);
    for (int i = 0; i < data.planetoid_number; ++i) {
        MapGenInfo map_gen_info;

        if (data.planetoid_number > 1) {
            LinearInterpolator interpolator;
            map_gen_info.size = interpolator.interpolate(((float) i) / (data.planetoid_number-1),
                                                         data.min_planetoid_size, data.max_planetoid_size);
        } else {
            map_gen_info.size = data.min_planetoid_size;
        }

        // TODO enemy spawning based on size and difficulty scaling
        for (int j = 0; j < 10; ++j) {
            map_gen_info.enemies_build_data.push_back(new BasicEnemyBuildData());
        }


        planetoid_data_vec.push_back(new PlanetoidPersistentData(map_gen_info));
    }
}

const std::vector<PlanetoidPersistentData *> &PlanetoidManager::get_planetoid_data_vec() const {
    return planetoid_data_vec;
}

