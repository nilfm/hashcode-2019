#include "output.cc"
#include "input.cc"
#include <cmath>
#include <vector>
#include <algorithm>

int dist(int ri, int ci, int rf, int cf) {
    return abs(rf-ri) + abs(cf-ci);
}

struct Ride {
    int ri, ci, rf, cf, s, f, num, real_s, real_f; 
};
