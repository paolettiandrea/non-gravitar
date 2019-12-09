#ifndef NON_GRAVITAR_CAMERAFOLLOW_HPP
#define NON_GRAVITAR_CAMERAFOLLOW_HPP

#include "SGE/logic/Logic.hpp"

#define ZOOM_SPEED 10

class CameraFollow : public sge::Logic {
public:
    CameraFollow(GameObject_H target);

    std::string get_logic_id() override;

    void on_update() override;

private:
    GameObject_H m_target;

};


#endif //NON_GRAVITAR_CAMERAFOLLOW_HPP
