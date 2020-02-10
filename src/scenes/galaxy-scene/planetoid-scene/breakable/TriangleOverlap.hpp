#ifndef NON_GRAVITAR_TRIANGLEOVERLAP_HPP
#define NON_GRAVITAR_TRIANGLEOVERLAP_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

typedef std::pair<double, double> TriPoint;

inline double Det2D(TriPoint &p1, TriPoint &p2, TriPoint &p3);

void CheckTriWinding(TriPoint &p1, TriPoint &p2, TriPoint &p3, bool allowReversed);

bool BoundaryCollideChk(TriPoint &p1, TriPoint &p2, TriPoint &p3, double eps);

bool BoundaryDoesntCollideChk(TriPoint &p1, TriPoint &p2, TriPoint &p3, double eps);

bool TriTri2D(TriPoint *t1,
              TriPoint *t2,
              double eps = 0.0, bool allowReversed = false, bool onBoundary = true);

#endif //NON_GRAVITAR_TRIANGLEOVERLAP_HPP
