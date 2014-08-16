#include <algorithm>
#include <iostream>
#include <vector>

bool greater (int a, int b) {return (a > b);}
bool less (int a, int b) {return (a < b);}

template <bool s>
struct selector {
    bool operator () (int a, int b) {return less(a,b);}
};

template <>
struct selector <false> {
    bool operator () (int a, int b) {return greater(a,b);}
};

int main()
{
   std::vector<int> vec {4,3,5,1};
   std::sort(vec.begin(), vec.end(), selector<true>{});
   
   for (auto i : vec) std::cout << i << " ";
   
   std::sort(vec.begin(), vec.end(), selector<false>{});
   
   std::cout << "\n";
    for (auto i : vec) std::cout << i << " ";
}
