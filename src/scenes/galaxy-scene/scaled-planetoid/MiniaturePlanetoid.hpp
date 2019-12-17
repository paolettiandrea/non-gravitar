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

    bool burn_fog(sge::Camera *camera);
protected:
    MarchingMap* m_scaled_marching_map;
    MarchingMap* m_scaled_secondary_marching_map;

    NoiseMap* scaled_fog_noisemap;
    MarchingMap *scaled_fog_background_marching_map;
public:
    MarchingMap *get_scaled_fog_background_marching_map() const;

public:
    NoiseMap *get_scaled_fog_noisemap() const;

protected:
    PlanetoidPersistentData* persistent_data;
    float grid_size;

    VertArray_H vert_array;

    static NoiseMap* downscale_noisemap(const NoiseMap &in, float grid_size, const NoiseMap &flood_map);
    static NoiseMap* downscale_noisemap(const NoiseMap &in, float grid_size);

    void clean_geometry();

    bool dirty_geometry_flag = true;

public:
    void make_geometry_dirty();

    void on_update() override;
};


#endif //NON_GRAVITAR_MINIATUREPLANETOID_HPP
