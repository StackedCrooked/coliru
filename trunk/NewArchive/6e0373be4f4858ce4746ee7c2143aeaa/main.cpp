#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v(100);
    std::iota(v.begin(),v.end(),1);
    std::vector<int> x = v;
    std::transform(v.begin(),v.end(),v.begin(),[](int a) { return a*a;});
    size_t totalOfV = std::accumulate(v.begin(),v.end(), 0);
    size_t totalOfX = std::accumulate(x.begin(),x.end(), 0);
    std::cout << (totalOfX*totalOfX) - totalOfV;
}