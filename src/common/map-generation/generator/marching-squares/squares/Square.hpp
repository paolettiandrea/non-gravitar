#ifndef NON_GRAVITAR_SQUARE_HPP
#define NON_GRAVITAR_SQUARE_HPP

#include <vector>
#include "ControlNode.hpp"

class Anchor {
public:
    Anchor(float normal_rotation, const sge::Vec2<float> &center_point);

    float get_normal_rotation() const;
    const sge::Vec2<float> &get_center_point() const;

private:
    float normal_rotation;
    sge::Vec2<float> center_point;
};

class Square {
public:
    enum SquareType {EMPTY, BOT_LEFT, BOT_RIGHT, BOT_LEFT_BOT_RIGHT,
        TOP_RIGHT, TOP_RIGHT_BOT_LEFT, TOP_RIGHT_BOT_RIGHT, TOP_RIGHT_BOT_LEFT_BOT_RIGHT,
        TOP_LEFT, TOP_LEFT_BOT_LEFT, TOP_LEFT_BOT_RIGHT, TOP_LEFT_BOT_LEFT_BOT_RIGHT, TOP_LEFT_TOP_RIGHT,
        TOP_LEFT_TOP_RIGHT_BOT_LEFT, TOP_LEFT_TOP_RIGHT_BOT_RIGHT, FULL};

    Square (ControlNode* top_left, ControlNode* top_right, ControlNode* bot_right, ControlNode* bot_left);

    ControlNode* top_left_cn;
    ControlNode* top_right_cn;
    ControlNode* bot_left_cn;
    ControlNode* bot_right_cn;

    std::vector<sge::Vec2<float>> get_fill_triangles() const;

    SquareType get_type() const;

    const bool is_edge() const;




private:

    void append_triangle(const sge::Vec2<float>& point1, const sge::Vec2<float>& point2, const sge::Vec2<float>& point3);

    std::vector<sge::Vec2<float>> m_triangles;

    void link_nodes(Node& n1, Node& n2);

    SquareType  m_type;

    std::vector<float> edge_normal_rotations;
public:
    const std::vector<float> &get_edge_normal_rotations() const;
    const bool has_rotation(float rot) const;

private:
    std::vector<sge::Vec2<float>> edge_centers;
public:
    const std::vector<sge::Vec2<float>> &get_edge_centers() const;
};




#endif //NON_GRAVITAR_SQUARE_HPP
