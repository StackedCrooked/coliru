#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
int main()
{
    std::set<int> v1{1,2,3,4,5,6,7,8};
    std::set<int> v2{        5,  7,  9,10};
 
    std::set<int> v_intersection;
 
    std::set_intersection(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          std::inserter(v_intersection, v_intersection.end()));
    for(int n : v_intersection)
        std::cout << n << ' ';
}
