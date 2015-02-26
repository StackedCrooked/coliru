#include <numeric>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <iostream>
#include <iomanip>
#include <ios>
#include <chrono>

typedef unsigned long long ullong;

ullong origional(ullong RANGE) {
    std::unordered_set<ullong> nums;

    for(ullong a=1; a<=RANGE; a++)
    {
        for(ullong b=a; b<=RANGE; b++)
        {
            for(ullong c=b; c<=RANGE; c++)
            {
                for(ullong d=c; d<=RANGE; d++)
                    nums.insert(a*b*c*d);
            }
        }
    }
    return nums.size();
}

const ullong small_range_max = 10000;

ullong solve_for_small_range(ullong nmax, ullong rmin, ullong rmax) {
    assert(rmax-rmin<=small_range_max);
    rmax -= 1;
    bool valid[small_range_max] = {};
    
    ullong amin = std::max(rmin/nmax/nmax/nmax, 1ull);
    ullong amax = std::min(rmax, nmax);
    for(ullong a=amin; a<=amax; a++)
    {
        ullong bmin = std::max(rmin/a/nmax/nmax, a);
        ullong bmax = std::min(rmax/a, nmax);
        for(ullong b=bmin; b<=bmax; b++)
        {
            ullong cmin = std::max(rmin/a/b/nmax, b);
            ullong cmax = std::min(rmax/a/b, nmax);
            for(ullong c=cmin; c<=cmax; c++)
            {
                ullong dmin = std::max(rmin/a/b/c, c);
                ullong dmax = std::min(rmax/a/b/c, nmax);
                for(ullong d=dmin; d<=dmax; d++)
                {
                    ullong res = a*b*c*d;
                    if (res>=rmin)
                        valid[res-rmin] = true;
                }
            }
        }
    }
    ullong result = std::accumulate(valid+0, valid+rmax-rmin+1, 0);
    return result;
}

ullong solve_for_large_range(ullong nmax) {
    ullong result = 0;
    ullong fullmax = nmax*nmax*nmax*nmax;
    for(ullong rmin=0; rmin<fullmax; rmin+=small_range_max) {
        ullong rmax = std::min(rmin+small_range_max, fullmax+1);
        result += solve_for_small_range(nmax, rmin, rmax);
    }
    return result;
}

void test(ullong nmax) {
    using namespace std::chrono;
    {
        auto begin = high_resolution_clock::now();
        ullong result = origional(nmax);
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<milliseconds>(end-begin);
        std::cout <<std::setw(9)<<"origional"<<"("<<std::setw(4)<<nmax;
        std::cout <<") found "<<std::setw(11)<<result;
        std::cout <<" in "<<std::setw(6)<<(dur.count()/1000.0)<<"s\n";
    }
    {
        auto begin = high_resolution_clock::now();
        ullong result = solve_for_large_range(nmax);
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<milliseconds>(end-begin);
        std::cout <<std::setw(9)<<"duck"<<"("<<std::setw(4)<<nmax;
        std::cout <<") found "<<std::setw(11)<<result;
        std::cout <<" in "<<std::setw(6)<<(dur.count()/1000.0)<<"s\n";
    }
}

#include <iostream>
int main(){
    const ullong num_tests = 19;
    ullong test_maxes[num_tests] = {4, 6, 9, 13, 17, 25, 35, 50, 71, 100, 141, 200, 282, 400, 565, 800, 1131, 1600, 2262};
    for(int i=0; i<num_tests; ++i)
        test(test_maxes[i]);

    return 0;
}