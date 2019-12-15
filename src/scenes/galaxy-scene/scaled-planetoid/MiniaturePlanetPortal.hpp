#ifndef NON_GRAVITAR_MINIATUREPLANETPORTAL_HPP
#define NON_GRAVITAR_MINIATUREPLANETPORTAL_HPP


#include "MiniaturePlanetoid.hpp"

class MiniaturePlanetPortal : public MiniaturePlanetoid {
public:
    MiniaturePlanetPortal(PlanetoidPersistentData *data, float grid_size);

    void on_start() override;

    std::string get_logic_id() override;

protected:
    Rigidbody_H m_rigidbody;
};


#endif //NON_GRAVITAR_MINIATUREPLANETPORTAL_HPP
