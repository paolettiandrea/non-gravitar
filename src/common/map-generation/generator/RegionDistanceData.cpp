//
// Created by andrea on 6/9/19.
//

#include "RegionDistanceData.hpp"
#include "Region.hpp"

RegionDistanceDataBundle::RegionDistanceDataBundle(std::vector<Region> yo) {

    for (int i = 0; i < yo.size(); ++i) {

        for (int j = i+1; j < yo.size(); ++j) {
            auto temp = Region::pseudo_distance(yo[i],yo[j]);
            map[IdTuple(i,j)] = temp;
        }
    }
}

RegionDistanceData RegionDistanceDataBundle::get_results(int region_id1, int region_id2) {
    if (region_id1==region_id2) {
        std::cout << "ERROR (RegionDistanceDataBundle): the two given region ids are tha same:" << region_id1 << std::endl;
        exit(1);
    }
    if (region_id1>region_id2) {
        std::swap(region_id1,region_id2);
    }
    return map[IdTuple(region_id1,region_id2)];
}
