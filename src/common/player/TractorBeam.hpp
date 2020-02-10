#ifndef NON_GRAVITAR_TRACTORBEAM_HPP
#define NON_GRAVITAR_TRACTORBEAM_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/VertArray.hpp>

#define NG_TRACTOR_BEAM_LENGHT 15.0
#define NG_TRACTOR_BEAM_ANGLE M_PI_4/2
#define NG_TRACTOR_BEAM_INITIAL_MASKED_LENGHT 1.5
#define NG_TRACTOR_BEAM_FORCE 8.0
#define NG_TRACTOR_BEAM_NUMBER_OF_SLICES 5

#define NG_TRACTOR_BEAM_KEY sf::Keyboard::N

class TractorBeam : public sge::Logic {
public:
    std::string get_logic_id() override;

    void on_start() override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

    void on_collision_end(sge::CollisionInfo &collision_info) override;

    void on_fixed_update() override;

    void on_update() override;

private:
    std::list<Rigidbody_H> colliding_bodies;

    VertArray_H vert_array;


};


#endif //NON_GRAVITAR_TRACTORBEAM_HPP
