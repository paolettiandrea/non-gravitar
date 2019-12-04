#ifndef NON_GRAVITAR_CONTROLNODE_HPP
#define NON_GRAVITAR_CONTROLNODE_HPP

#include "Node.hpp"

class ControlNode {
public:
    ControlNode(bool val, sge::Vec2<float> _position) : active(val), position(_position), down_node(position+sge::Vec2<float>(0.5f,0)), right_node(position+sge::Vec2<float>(0,0.5f)) {};
    sge::Vec2<float> position;
    bool active;
    Node right_node;
    Node down_node;
};


#endif //NON_GRAVITAR_CONTROLNODE_HPP
