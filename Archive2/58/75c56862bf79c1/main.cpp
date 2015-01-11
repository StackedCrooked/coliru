#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

int main() {
#ifdef NDEBUG
    typedef double T;
    struct coord { T x,y,z; };

    coord rmin { 0,  1,  2 },
          imin { 3,  4,  5 },
          imax { 6,  7,  8 },
          rmax { 9, 10, 11 };
#else
    typedef const char* T;
    struct coord { T x,y,z; };

    coord rmin { "rmin.x", "rmin.y", "rmin.z" },
          imin { "imin.x", "imin.y", "imin.z" },
          imax { "imax.x", "imax.y", "imax.z" },
          rmax { "rmax.x", "rmax.y", "rmax.z" };
#endif
    using namespace std;

    // the source sequence
    coord const sequence[] = { rmin, imin, imax, rmax };

    // we take all consecutive pairs (warning: ignoring the `(rmax, rmin)` closing pair here)
    vector<pair<coord, coord>> pairs;
    transform(begin(sequence), prev(end(sequence)), back_inserter(pairs), [](coord const& it) { return std::make_pair(*(&it+0), *(&it+1)); });

    // Now we build cubes. The `make_cube` interface implied it requires two
    // coordinates to be constructed:
    struct Cube { coord p1, p2; };
    std::array<Cube, 3*3*3> cubes;

    // generate!
    auto out = cubes.begin();
    for (auto zs : pairs) for (auto ys : pairs) for (auto xs : pairs)
        *out++ = Cube { { xs.first.x, ys.first.y, zs.first.z }, { xs.second.x, ys.second.y, zs.second.z } }; 

    // debug print
    for(auto const& c : cubes)
        std::cout << "make_cube(" << c.p1.x << ", " << c.p1.y << ", " << c.p1.z << ", " << c.p2.x << ", " << c.p2.y << ", " << c.p2.z << ")\n";
}


