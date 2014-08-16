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

template<class RndIt, class Equal = std::equal_to<>, class Compare = std::less<>>
void sort_within(RndIt first, RndIt last, Equal eq = Equal{}, Compare cmp = Compare{})
{
    for (auto it = first; it != last; /* increment inside loop */) {
        auto next = std::find_if_not(it, last, [=](auto const& elem){
            return eq(elem, *it);
        });
        std::sort(it, next, cmp);
        it = next;
    }
}

int main()
{
    using Elem = std::pair<int, int>;
    
    auto v = std::vector<Elem> { {0,2}, {1,2}, {3,2}, {4,0}, {0,1}, {2,2}, {1,1}, {2,0}, {4,2}, {3,1} };    
    std::cout << "input data: \n";
    for (auto&& e : v)
        std::cout << "{" << e.first << "," << e.second << "}, ";
    std::cout << "\n\n";
    
    cluster(begin(v), end(v), [](auto const& L, auto const& R){
        return L.first == R.first;
    });
    std::cout << "after clustering: \n";    
    for (auto&& e : v)
        std::cout << "{" << e.first << "," << e.second << "}, ";
    std::cout << "\n\n";

    sort_within(begin(v), end(v), 
        [](auto const& L, auto const& R){ return L.first == R.first; },
        [](auto const& L, auto const& R){ return L.second < R.second; }
    );
    std::cout << "after sorting within clusters: \n";
    for (auto&& e : v)
        std::cout << "{" << e.first << "," << e.second << "}, ";
    std::cout << "\n";
}