#include "Square.hpp"
#include "cmath"


Square::Square(ControlNode* top_left, ControlNode* top_right, ControlNode* bot_right, ControlNode* bot_left)
        : top_left_cn(top_left), top_right_cn(top_right), bot_right_cn(bot_right) , bot_left_cn(bot_left) {

    unsigned int lookup_index = 0;
    if (top_left_cn->active) lookup_index += 1 << 3;
    if (top_right_cn->active) lookup_index += 1 << 2;
    if (bot_right_cn->active) lookup_index += 1 << 1;
    if (bot_left_cn->active) lookup_index += 1;

    m_type = static_cast<SquareType>(lookup_index);

    switch (m_type) {
        case EMPTY:
            break;

        case BOT_LEFT:
            link_nodes(top_left_cn->down_node, bot_left_cn->right_node);
            append_triangle(top_left_cn->down_node.position, bot_left_cn->position, bot_left_cn->right_node.position);

            edge_normal_rotations.push_back(-M_PI_4);
            edge_centers.push_back((top_left->down_node.position + bot_left->right_node.position)/2);
            break;

        case BOT_RIGHT:
            link_nodes(bot_left_cn->right_node, top_right_cn->down_node);
            append_triangle(top_right_cn->down_node.position, bot_left_cn->right_node.position, bot_right_cn->position);

            edge_normal_rotations.push_back(M_PI_4);
            edge_centers.push_back((bot_left_cn->right_node.position + top_right_cn->down_node.position)/2);
            break;

        case BOT_LEFT_BOT_RIGHT:
            link_nodes(top_left_cn->down_node, top_right_cn->down_node);
            append_triangle(top_right_cn->down_node.position, bot_right_cn->position, bot_left_cn->position);
            append_triangle(top_left_cn->down_node.position, bot_left_cn->position, top_right_cn->down_node.position);

            edge_normal_rotations.push_back(0);
            edge_centers.push_back((top_left_cn->down_node.position + top_right_cn->down_node.position)/2);
            break;

        case TOP_RIGHT:
            link_nodes(top_right_cn->down_node, top_left_cn->right_node);
            append_triangle(top_right_cn->down_node.position, top_right_cn->position, top_left_cn->right_node.position);

            edge_normal_rotations.push_back(3.0/4.0*M_PI);
            edge_centers.push_back((top_right_cn->down_node.position + top_left_cn->right_node.position)/2);
            break;

        case TOP_RIGHT_BOT_LEFT:
            link_nodes(top_left_cn->right_node, top_left_cn->down_node);
            link_nodes(top_right_cn->down_node, bot_left_cn->right_node);

            edge_normal_rotations.push_back(M_PI_4);
            edge_centers.push_back((top_left_cn->right_node.position + top_left_cn->down_node.position)/2);
            edge_normal_rotations.push_back(-3.0/4.0*M_PI);
            edge_centers.push_back((top_right_cn->down_node.position + bot_left_cn->right_node.position)/2);

            append_triangle(bot_left_cn->position, top_left_cn->right_node.position, top_left_cn->down_node.position);
            append_triangle(bot_left_cn->position, bot_left_cn->right_node.position, top_right_cn->position);
            append_triangle(bot_left_cn->position, top_right_cn->position, top_left_cn->right_node.position);
            append_triangle(bot_left_cn->right_node.position, top_right_cn->down_node.position, top_right->position);
            break;

        case TOP_RIGHT_BOT_RIGHT:
            link_nodes(top_left_cn->right_node, bot_left_cn->right_node);
            append_triangle(top_right_cn->position, bot_right_cn->position, top_left_cn->right_node.position);
            append_triangle(top_left_cn->right_node.position, bot_left_cn->right_node.position, bot_right_cn->position);

            edge_normal_rotations.push_back(M_PI_2);
            edge_centers.push_back((top_left_cn->right_node.position + bot_left_cn->right_node.position)/2);
            break;

        case TOP_RIGHT_BOT_LEFT_BOT_RIGHT:
            link_nodes(top_left_cn->right_node, top_left_cn->down_node);
            append_triangle(top_left_cn->down_node.position, bot_left_cn->position, top_left_cn->right_node.position);
            append_triangle(top_left_cn->right_node.position, bot_left_cn->position, top_right_cn->position);
            append_triangle(top_right_cn->position, bot_left_cn->position, bot_right_cn->position);

            edge_normal_rotations.push_back(M_PI_4);
            edge_centers.push_back((top_left_cn->right_node.position + top_left_cn->down_node.position)/2);
            break;

        case TOP_LEFT:
            link_nodes(top_left_cn->right_node, top_left_cn->down_node);
            append_triangle(top_left_cn->right_node.position, top_left_cn->position, top_left_cn->down_node.position);

            edge_normal_rotations.push_back(-3.0/4.0*M_PI);
            edge_centers.push_back((top_left_cn->right_node.position + top_left_cn->down_node.position)/2);
            break;

        case TOP_LEFT_BOT_LEFT:
            link_nodes(top_left_cn->right_node, bot_left_cn->right_node);
            append_triangle(top_left_cn->right_node.position, top_left_cn->position, bot_left_cn->position);
            append_triangle(top_left_cn->right_node.position, bot_left_cn->position, bot_left_cn->right_node.position);

            edge_normal_rotations.push_back(-M_PI_2);
            edge_centers.push_back((top_left_cn->right_node.position + bot_left_cn->right_node.position)/2);
            break;

        case TOP_LEFT_BOT_RIGHT:
            link_nodes(top_left_cn->down_node, bot_left_cn->right_node);
            link_nodes(top_right_cn->down_node, top_left_cn->right_node);

            edge_normal_rotations.push_back(3.0/4.0*M_PI);
            edge_centers.push_back((top_left_cn->down_node.position + bot_left_cn->right_node.position)/2);
            edge_normal_rotations.push_back(-M_PI_4);
            edge_centers.push_back((top_right_cn->down_node.position + top_left_cn->right_node.position)/2);

            append_triangle(top_left_cn->down_node.position, bot_left_cn->right_node.position, bot_right_cn->position);
            append_triangle(top_left_cn->down_node.position, bot_right_cn->position, top_left_cn->position);
            append_triangle(top_left_cn->position, bot_right_cn->position, top_right_cn->down_node.position);
            append_triangle(top_left_cn->position, top_right_cn->down_node.position, top_left_cn->right_node.position);
            break;

        case TOP_LEFT_BOT_LEFT_BOT_RIGHT:
            link_nodes(top_right_cn->down_node, top_left_cn->right_node);
            append_triangle(top_left_cn->position, bot_left_cn->position, top_left_cn->right_node.position);
            append_triangle(top_left_cn->right_node.position, bot_left_cn->position, bot_right_cn->position);
            append_triangle(top_left_cn->right_node.position, bot_right_cn->position, top_right_cn->down_node.position);

            edge_normal_rotations.push_back(-M_PI_4);
            edge_centers.push_back((top_right_cn->down_node.position + top_left_cn->right_node.position)/2);
            break;

        case FULL:
            append_triangle(top_left_cn->position, bot_left_cn->position, bot_right_cn->position);
            append_triangle(top_left_cn->position, bot_right_cn->position, top_right_cn->position);
            break;
        case TOP_LEFT_TOP_RIGHT:
            link_nodes(top_left_cn->down_node, top_right_cn->down_node);
            append_triangle(top_left_cn->position, top_left_cn->down_node.position, top_right_cn->position);
            append_triangle(top_right_cn->position, top_left_cn->down_node.position, top_right_cn->down_node.position);

            edge_normal_rotations.push_back(M_PI);
            edge_centers.push_back((top_left_cn->down_node.position + top_right_cn->down_node.position)/2);
            break;

        case TOP_LEFT_TOP_RIGHT_BOT_LEFT:
            link_nodes(bot_left_cn->right_node, top_right_cn->down_node);
            append_triangle(top_left_cn->position, bot_left_cn->position, top_right_cn->position);
            append_triangle(bot_left_cn->position, top_right_cn->position, bot_left_cn->right_node.position);
            append_triangle(top_right_cn->position, top_right_cn->down_node.position, bot_left_cn->right_node.position);

            edge_normal_rotations.push_back(-3.0/4.0*M_PI);
            edge_centers.push_back((bot_left_cn->right_node.position + top_right_cn->down_node.position)/2);
            break;

        case TOP_LEFT_TOP_RIGHT_BOT_RIGHT:
            link_nodes(top_left_cn->down_node, bot_left_cn->right_node);
            append_triangle(top_left_cn->down_node.position, bot_left_cn->right_node.position, bot_right_cn->position);
            append_triangle(top_left_cn->down_node.position, bot_right_cn->position, top_left_cn->position);
            append_triangle(top_left_cn->position, bot_right_cn->position, top_right_cn->position);

            edge_normal_rotations.push_back(3.0/4.0*M_PI);
            edge_centers.push_back((top_left_cn->down_node.position + bot_left_cn->right_node.position)/2);
            break;
    }
}

void Square::link_nodes(Node& n1, Node& n2) {
    n1.link(n2);
    n2.link(n1);
}

void Square::append_triangle(const sge::Vec2<float>& point1, const sge::Vec2<float>& point2, const sge::Vec2<float>& point3) {
    m_triangles.emplace_back(point1.x, point1.y);
    m_triangles.emplace_back(point2.x, point2.y);
    m_triangles.emplace_back(point3.x, point3.y);
}

std::vector<sge::Vec2<float>> Square::get_fill_triangles() const {
    return m_triangles;
}

Square::SquareType Square::get_type() const {
    return m_type;
}

const bool Square::is_edge() const {
    return (m_type!=FULL && m_type!=EMPTY);
}

const std::vector<float> &Square::get_edge_normal_rotations() const {
    return edge_normal_rotations;
}

const bool Square::has_rotation(float rot) const {
    for (int i = 0; i < edge_normal_rotations.size(); ++i) {
        if (edge_normal_rotations[i] == rot) return true;
    }
    return false;
}

const std::vector<sge::Vec2<float>> &Square::get_edge_centers() const {
    return edge_centers;
}

Anchor::Anchor(float normal_rotation, const sge::Vec2<float> &center_point) : normal_rotation(normal_rotation),
                                                                              center_point(center_point) {}

float Anchor::get_normal_rotation() const {
    return normal_rotation;
}

const sge::Vec2<float> &Anchor::get_center_point() const {
    return center_point;
}
