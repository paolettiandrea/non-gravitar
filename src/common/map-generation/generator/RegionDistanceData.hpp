//
// Created by andrea on 6/9/19.
//

#ifndef PERLIN_TESTS_REGIONDISTANCEDATA_HPP
#define PERLIN_TESTS_REGIONDISTANCEDATA_HPP

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
#include "vector"
#include "map"
#include "SGE/Vec2.hpp"


struct RegionDistanceData {
    float pseudo_distance = 0.f;
    sge::Vec2<int> p1, p2;
};

struct IdTuple {
    IdTuple(int _id1, int _id2) : id1(_id1), id2(_id2) {}
    int id1;
    int id2;

    bool operator<(const IdTuple& rhs) const {
        if (id1 == rhs.id1){
            if (id2 < rhs.id2) { return true; }
        } else {
            if (id1 < rhs.id1) return true;
        }
        return false;
    }

    bool operator>(const IdTuple& rhs) const {
        return rhs < *this;
    }

    bool operator<=(const IdTuple& rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const IdTuple& rhs) const {
        return !(*this < rhs);
    }

};

class Region;
struct RegionDistanceDataBundle {
    RegionDistanceDataBundle(std::vector<Region> region_vec);

    RegionDistanceData get_results(int region_id1, int region_id2);

private:
    std::map<IdTuple,RegionDistanceData> map;
};

#endif //PERLIN_TESTS_REGIONDISTANCEDATA_HPP
