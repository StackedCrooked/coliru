#include <numeric>
#include <algorithm>
#include <cassert>

typedef unsigned long long ullong;
const ullong small_range_max = 10000;

ullong solve_for_small_range(ullong nmax, ullong rmin, ullong rmax) {
    assert(rmax-rmin<=small_range_max);
    bool valid[small_range_max] = {};
    ullong amax = std::min(rmax, nmax);
    for(ullong a=1; a<=amax; a++)
    {
        ullong bmax = std::min(rmax/a, nmax);
        for(ullong b=a; b<=bmax; b++)
        {
            ullong cmax = std::min(rmax/a/b, nmax);
            for(ullong c=b; c<=cmax; c++)
            {
                ullong dmin = std::max(rmin/a/b/c, c);
                ullong dmax = std::min(rmax/a/b/c, nmax);
                for(ullong d=dmin; d<=dmax; d++)
                {
                    ullong res = a*b*c*d;
                    if (res>=rmin && res<rmax)
                        valid[res-rmin] = true;
                }
            }
        }
    }
    return std::accumulate(valid+0, valid+rmax-rmin, 0);
}

ullong solve_for_large_range(ullong nmax) {
    ullong result = 0;
    ullong fullmax = nmax*nmax*nmax*nmax;
    for(ullong rmin=0; rmin<fullmax; rmin+=small_range_max) {
        ullong rmax = std::min(rmin+small_range_max, fullmax);
        result += solve_for_small_range(nmax, rmin, rmax);
    }
    return result;
}

#include <iostream>
int main(){

    ullong result = solve_for_large_range(85);
    std::cout << result;

    return 0;
}