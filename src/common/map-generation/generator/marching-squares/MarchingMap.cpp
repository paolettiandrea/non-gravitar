#include "MarchingMap.hpp"
#include "cmath"

MarchingMap::MarchingMap(const NoiseMap &map, float threshold, bool invert): width(map.width-1), height(map.height-1) {
    // Create ControlNode grid
    ControlNode ***control_node_grid;
    control_node_grid = new ControlNode **[map.width];
    for (int k = 0; k < map.width; ++k) {
        control_node_grid[k] = new ControlNode *[map.height];
        for (int i = 0; i < map.height; ++i) {
            if (invert) {
                control_node_grid[k][i] = new ControlNode(map[k][i] > threshold, sge::Vec2<float>(k, i));
            } else {
                control_node_grid[k][i] = new ControlNode(map[k][i] < threshold, sge::Vec2<float>(k, i));
            }
        }
    }

    // Allocate square grid
    for (int i = 0; i < width; ++i) {
        square_grid.emplace_back();
        for (int j = 0; j < height; ++j) {
            square_grid[i].emplace_back(control_node_grid[i][j], control_node_grid[i][j + 1],
                                        control_node_grid[i + 1][j + 1], control_node_grid[i + 1][j]);
        }
    }


    // Define delimiting paths
    for (int k = 0; k < height; ++k) {
        for (int i = 0; i < width; ++i) {
            Node* target_node = &square_grid[k][i].top_left_cn->right_node;
            if (!target_node->checked_flag && target_node->is_edge) {
                // Found a new path
                paths.emplace_back();
                Node* starting_node = target_node;
                Node* previous_node = nullptr;
                Node* pointed_node = starting_node;
                sge::Vec2<float> previous_direction = sge::Vec2<float>(0,0);
                bool done = false;
                while (!done) {
                    pointed_node->checked_flag = true;
                    auto temp = pointed_node;
                    pointed_node = pointed_node->get_linked(previous_node);
                    if (pointed_node->position-temp->position != previous_direction) {
                        paths.back().append_point(sge::Vec2<float>(temp->position));
                        previous_direction = pointed_node->position-temp->position;
                    }
                    if (pointed_node!= nullptr && pointed_node!=starting_node) {
                        previous_node = temp;
                    } else {
                        done = true;
                    }
                }
            } else {
                target_node->checked_flag = true;
            }
        }
    }


}

const std::vector<sge::Path> &MarchingMap::get_paths() const {
    return paths;
}

Square &MarchingMap::get_square(unsigned int row, unsigned int column) {
    return square_grid[row][column];
}
const Square &MarchingMap::get_square(unsigned int row, unsigned int column) const {
    return square_grid[row][column];
}

Square &MarchingMap::operator[](sge::Vec2<int> coords) {
    return square_grid[coords.x][coords.y];
}

const Square &MarchingMap::operator[](sge::Vec2<int> coords) const {
    return square_grid[coords.x][coords.y];
}

const float MarchingMap::get_edge_safe_distance(unsigned int row, unsigned int column) const {
    const Square* pointed_square = &get_square(row, column);
    if (pointed_square->is_edge()){
        auto rotations = square_grid[row][column].get_edge_normal_rotations();
        // For every rotation of the starting square trace the straight edge both ways and see
        for (int i = 0; i < rotations.size(); ++i) {
            float step_lenght;
            if (rotations[i]==M_PI_2 || rotations[i]==0 || rotations[i]==-M_PI_2 || rotations[i]==M_PI || rotations[i]==-M_PI) {
                step_lenght = 1;
            } else {
                step_lenght = std::sqrt(0.5*0.5+0.5*0.5);
            }
            auto first_coord = get_next_square_coords(coord(row, column), coord(-1,-1), rotations[i]);
            auto second_coord = get_next_square_coords(coord(row, column), first_coord, rotations[i]);

            int first_steps = 0;
            int second_steps = 0;
            if (first_coord!=coord(-1,-1)) {
                first_steps = recursive_stepper(first_coord, coord(row, column), rotations[i], 1);
                if (second_coord != coord(-1, -1)) {
                    second_steps = recursive_stepper(second_coord, coord(row, column), rotations[i], 1);
                }
            }
            float out = step_lenght/2 + std::min(first_steps, second_steps)*step_lenght;
            return out;
        }

    } else {
        std::cout << "ERROR: the given point is not an edge" << std::endl;
        exit(1);
    }
    return 0;
}

const coord MarchingMap::get_next_square_coords(coord pointed_square, coord avoid_square, float target_rotation) const {
    auto angle_matches = get_angle_matches(pointed_square, target_rotation);
        if (angle_matches.size()<=2) {
            for (auto & angle_match_coord : angle_matches) {
                if (angle_match_coord != avoid_square) return angle_match_coord;
            }
            return coord(-1, -1);
        } else {
            std::cout << "ERROR: wrong number of squares with the same angle" << std::endl;
            exit(1);
        }
}

const std::vector<coord> MarchingMap::get_angle_matches(coord pointed_square, float target_rotation) const {
    std::vector<coord> angle_matches;

    if (square_grid[pointed_square.x][pointed_square.y].is_edge()) {
        coord match_coord = coord(pointed_square.x + 1, pointed_square.y);
        if (match_coord.x < width - 1 &&
            square_grid[match_coord.x][match_coord.y].has_rotation(target_rotation))
            angle_matches.push_back(match_coord);
        match_coord = coord(pointed_square.x, pointed_square.y + 1);
        if (match_coord.y < height - 1 &&
            square_grid[match_coord.x][match_coord.y].has_rotation(target_rotation))
            angle_matches.push_back(match_coord);
        match_coord = coord(pointed_square.x - 1, pointed_square.y);
        if (match_coord.x > 0 && square_grid[match_coord.x][match_coord.y].has_rotation(target_rotation))
            angle_matches.push_back(match_coord);
        match_coord = coord(pointed_square.x, pointed_square.y - 1);
        if (match_coord.y > 0 && square_grid[match_coord.x][match_coord.y].has_rotation(target_rotation))
            angle_matches.push_back(match_coord);
    }

    return angle_matches;
}

const int MarchingMap::recursive_stepper(coord point, coord exclude, float rot_target, int counter) const {
    auto next = get_next_square_coords(point, exclude, rot_target);
    if (next==coord(-1,-1)) return counter;
    else return recursive_stepper(next, point, rot_target, counter+1);
}




