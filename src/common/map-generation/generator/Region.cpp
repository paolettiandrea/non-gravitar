#include "Region.hpp"
#include "RegionDistanceData.hpp"

int Region::unique_index_counter = 0;

void Region::flood_fill(const NoiseMap& map, int _x, int _y, float target_val, Matrix2D<bool>& checked_flags_matrix) {
    using sge::Vec2;
    std::queue<Vec2<int>> to_evaluate_queue;
    to_evaluate_queue.emplace(_x,_y);

    while (!to_evaluate_queue.empty()) {
        auto initial_queue_size = to_evaluate_queue.size();
        for (int i = 0; i < initial_queue_size; ++i) {
            auto coords = to_evaluate_queue.front();
            if (!checked_flags_matrix[coords.x][coords.y] && map[coords.x][coords.y] == target_val) {
                // This point wasn't considered before and is empty, so it can be added to the region list
                m_points.emplace_back(coords.x, coords.y);
                checked_flags_matrix[coords.x][coords.y] = true;
                m_volume++;

                // Add the four adjacent points to be considered at the next loop
                bool border_flag = false;
                if (coords.x>0) {
                    to_evaluate_queue.emplace(coords.x-1,coords.y);
                    if (map[coords.x-1][coords.y]!=target_val) border_flag = true;
                }
                if (coords.x<map.width-1){
                    to_evaluate_queue.emplace(coords.x+1, coords.y);
                    if (map[coords.x+1][coords.y]!=target_val) border_flag = true;
                }
                if (coords.y>0) {
                    to_evaluate_queue.emplace(coords.x,coords.y-1);
                    if (map[coords.x][coords.y-1]!=target_val) border_flag = true;
                }
                if (coords.y<map.height-1) {
                    to_evaluate_queue.emplace(coords.x, coords.y+1);
                    if (map[coords.x][coords.y+1]!=target_val) border_flag = true;
                }

                if (border_flag) m_border_points.emplace_back(coords.x,coords.y);
            }
            to_evaluate_queue.pop();
        }
    }
}

RegionDistanceData Region::pseudo_distance(Region& region1, Region& region2) {
    RegionDistanceData out_data;
    out_data.pseudo_distance = std::numeric_limits<float>::max();
    for (int i1 = 0; i1 < region1.m_border_points.size(); i1 += 10) {
        for (int i2 = 0; i2 < region2.m_border_points.size(); i2 += 10) {
            float distance = pow(region1.m_border_points[i1].x - region2.m_border_points[i2].x,2) +
                                   pow(region1.m_border_points[i1].y - region2.m_border_points[i2].y,2);
            if (distance < out_data.pseudo_distance) {
                out_data.pseudo_distance = distance;
                out_data.p1 = region1.m_border_points[i1];
                out_data.p2 = region2.m_border_points[i2];
            }
        }
    }
    return  out_data;
}

std::ostream& operator<<(std::ostream& os, const Region& region) {
    os << "Region: volume[" << region.m_volume
       << "]\t border[" << region.m_border_points.size() << "]\t unique_index[: " << region.m_unique_index << "]";
    return os;
}

bool Region::is_connected(const Region& other_region) {
    for (int i = 0; i < connected_rooms.size(); ++i) {
        if (connected_rooms[i] == other_region.m_unique_index) {
            return true;
        }
    }
    return false;
}

void Region::set_connected(const Region& other_region) {
    connected_rooms.push_back(other_region.m_unique_index);
}

bool Region::contains(sge::Vec2<int> point) {
    for (int i = 0; i < m_points.size(); ++i) {
        if (m_points[i] == point) return true;
    }
    return false;
}

void Region::fill_with_val(NoiseMap& map, float val) {
    for (int i = 0; i < m_points.size(); ++i) {
        map[m_points[i].x][m_points[i].y] = val;
    }
}
