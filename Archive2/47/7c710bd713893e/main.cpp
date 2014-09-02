#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

template<class FwdIt, class Equal = std::equal_to<>>
void cluster(FwdIt first, FwdIt last, Equal eq = Equal{}) 
{
    for (auto it = first; it != last; /* increment inside loop */)
        it = std::partition(it, last, [=](auto const& elem){
            return eq(elem, *it);    
        });    
}

int main()
{
    using Elem = int;
    
    auto v = std::vector<Elem> { 0, 1, 3, 4, 0, 2, 1, 2, 4, 3 };    
    std::cout << "input data: \n";
    for (auto&& e : v)
        std::cout << e << ", ";
    std::cout << "\n\n";
    
    cluster(begin(v), end(v));
    std::cout << "after clustering: \n";    
    for (auto&& e : v)
        std::cout << e << ", ";
    std::cout << "\n\n";

    v.erase(std::unique(begin(v), end(v)), end(v));
    std::cout << "after erase-removing duplicates: \n";
    for (auto&& e : v)
        std::cout << e << ", ";
    std::cout << "\n";
}