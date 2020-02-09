#ifndef NON_GRAVITAR_PLANETOIDMANAGER_HPP
#define NON_GRAVITAR_PLANETOIDMANAGER_HPP

#include <SGE/logic/Logic.hpp>
#include <PlanetoidPersistentData.hpp>
#include <Galaxy_ConstructionData.hpp>
#include "EnemyBuildData.hpp"



/*!
 * \brief Generates and manages the Planetoids persistent data
 */
class PlanetoidManager : public sge::Logic {
public:
    explicit PlanetoidManager(const Galaxy_ConstructionData& data);
    std::string get_logic_id() override;

    virtual ~PlanetoidManager();

    [[nodiscard]] const std::vector<PlanetoidPersistentData *> &get_planetoid_data_vec() const;



private:
    std::vector<PlanetoidPersistentData*> planetoid_data_vec;

    void add_special_crates(MapGenInfo& map_gen_info);
};

#endif //NON_GRAVITAR_PLANETOIDMANAGER_HPP
