#ifndef NON_GRAVITAR_PLANETOIDMANAGER_HPP
#define NON_GRAVITAR_PLANETOIDMANAGER_HPP

#include <SGE/logic/Logic.hpp>
#include <PlanetoidData.hpp>

#define NON_GRAVITAR_GENERATED_PLANETOIDS 1

/*!
 * \brief Generates and manages the Planetoids raw data
 */
class PlanetoidManager : public sge::Logic {
public:
    std::string get_logic_id() override;

    void on_start() override;

    void generate_planetoids();

private:
    PlanetoidData* planetoid_data[NON_GRAVITAR_GENERATED_PLANETOIDS];
};

#endif //NON_GRAVITAR_PLANETOIDMANAGER_HPP
