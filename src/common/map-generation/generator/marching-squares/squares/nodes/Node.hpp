#ifndef NON_GRAVITAR_NODE_HPP
#define NON_GRAVITAR_NODE_HPP

#include "SGE/Vec2.hpp"

class Node {
public:
    Node(sge::Vec2<float> _position) : position(_position) {}
    sge::Vec2<float> position;
    bool is_edge = false;
    Node* linked1 = nullptr;
    Node* linked2 = nullptr;
    bool checked_flag = false;

    void link(Node& n2);

    Node* get_linked(Node* exclude_linked=nullptr);
};


#endif //NON_GRAVITAR_NODE_HPP
