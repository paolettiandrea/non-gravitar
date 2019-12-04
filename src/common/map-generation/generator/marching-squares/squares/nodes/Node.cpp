#include "Node.hpp"

#include <iostream>

Node* Node::get_linked(Node* exclude_linked) {
    if (is_edge) {
        if (exclude_linked==nullptr) {
            // If a exclude_linked is not given basically chose a random direction
            if (linked1!= nullptr) return linked1;
            else if (linked2!= nullptr) return  linked2;
            else {
                std::cout << "Error: couldn't return a linked node" << std::endl;
                exit(1);
            }
        } else {
            if (linked1==exclude_linked) return linked2;
            else if (linked2 == exclude_linked) return  linked1;
            else {
                std::cout << "Error: couldn't return a linked node because the exclude_linked pointer doesn't match neither of the linked nodes" << std::endl;
                exit(1);
            }
        }
    } else {
        std::cout << "Error: couldn't return a linked node because the node is not part of an edge" << std::endl;
        exit(1);
    }
}

void Node::link(Node& n2) {
    if (linked1 == nullptr) linked1 = &n2;
    else {
        if (linked2 == nullptr) linked2 = &n2;
        else {
            std::cout << "Error: tried to link a node that was already completely linked" << std::endl;
            exit(1);
        }
    }
    is_edge = true;
}