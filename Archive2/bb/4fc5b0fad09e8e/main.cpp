#include <iostream>
#include <algorithm>
#include <vector>

template <typename FI>
void sorta(FI begin, FI end){
    using T = typename std::iterator_traits<FI>::value_type;
    std::sort(begin, end, [](const T& lhs,const T& rhs){
         std::cout << lhs<<"**"<<&lhs  << '\n';
         return std::rand()%2;
    });
}

int main()
{
    srand(8);
    
    std::vector<int> a{1,5,3,4,7};
    sorta(a.begin(),a.end());
}
