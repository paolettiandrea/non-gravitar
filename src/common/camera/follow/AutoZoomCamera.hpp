#ifndef NON_GRAVITAR_AUTOZOOMCAMERA_HPP
#define NON_GRAVITAR_AUTOZOOMCAMERA_HPP


#include "SmoothCamera.hpp"

class AutoZoomCamera : public SmoothCamera {
public:
    AutoZoomCamera(sge::Vec2<float> center, float radius, float base_zoom);


    std::string get_logic_id() override;

protected:
    void update_target_zoom() override;

private:
    sge::Vec2<float> center;
    float radius;
    float base_zoom;
};


#endif //NON_GRAVITAR_AUTOZOOMCAMERA_HPP
