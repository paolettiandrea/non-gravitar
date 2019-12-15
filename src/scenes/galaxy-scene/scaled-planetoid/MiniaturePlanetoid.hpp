#ifndef NON_GRAVITAR_MINIATUREPLANETOID_HPP
#define NON_GRAVITAR_MINIATUREPLANETOID_HPP


#include <SGE/logic/Logic.hpp>
#include "PlanetoidPersistentData.hpp"
#include "Planetoid.hpp"


class MiniaturePlanetoid: public sge::Logic {
public:
    explicit MiniaturePlanetoid(PlanetoidPersistentData* data, float grid_size);

    explicit MiniaturePlanetoid(MiniaturePlanetoid *base);

    void on_start() override;

    PlanetoidPersistentData* get_planetoid_persistent_data() { return persistent_data; }

    virtual ~MiniaturePlanetoid();

    MarchingMap *get_scaled_secondary_marching_map() const;

    MarchingMap *get_scaled_marching_map() const;

    [[nodiscard]] float get_grid_size() const;
protected:
    MarchingMap* m_scaled_marching_map;
    MarchingMap* m_scaled_secondary_marching_map;
    PlanetoidPersistentData* persistent_data;
    float grid_size;

    static NoiseMap* downscale_noisemap(const NoiseMap &in, float grid_size, const NoiseMap &flood_map);
    static NoiseMap* downscale_noisemap(const NoiseMap &in, float grid_size);
};


#endif //NON_GRAVITAR_MINIATUREPLANETOID_HPP
