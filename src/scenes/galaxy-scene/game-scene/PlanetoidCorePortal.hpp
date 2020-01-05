#ifndef NON_GRAVITAR_PLANETOIDCOREPORTAL_HPP
#define NON_GRAVITAR_PLANETOIDCOREPORTAL_HPP

#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/VertArray.hpp>

#define NG_PLANETOID_CORE_PORTAL_LAYER_NUMBER 5
#define NG_PLANETOID_CORE_PORTAL_MIN_RADIUS 0.5
#define NG_PLANETOID_CORE_PORTAL_MAX_RADIUS 5.0
#define NG_PLANETOID_CORE_PORTAL_ROTATION_OUTER_VEL 1.0
#define NG_PLANETOID_CORE_PORTAL_ROTATION_INNER_VEL 2.5
#define NG_PLANETOID_CORE_PORTAL_ROTATION_TOP_COLOR sf::Color(200, 200, 0)
#define NG_PLANETOID_CORE_PORTAL_ROTATION_BOTTOM_COLOR sf::Color(100, 100, 0)
#define NG_PLANETOID_CORE_PORTAL_ACCEL_DURATION 2.0

class PlanetoidCorePortal : public sge::Logic {
public:
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    GameObject_H triangles_gos[NG_PLANETOID_CORE_PORTAL_LAYER_NUMBER];
    float triangle_vels[NG_PLANETOID_CORE_PORTAL_LAYER_NUMBER];
};


#endif //NON_GRAVITAR_PLANETOIDCOREPORTAL_HPP
