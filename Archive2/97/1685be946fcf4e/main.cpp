#include <random>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>
#include <algorithm>

std::pair<int, int> lexicographic_pair_helper(int p, int maxDigits)
{
    int digits = std::log10(p);
    int l = p*std::pow(10, maxDigits-digits);
    return {l, p};
}

int main()
{
    std::vector<int> v = {100, 21 , 22 , 99 , 1  , 927};
    
    auto max = *std::max_element(begin(v), end(v));
    int maxDigits = std::log10(max);
    
    std::vector<std::pair<int,int>> v2;
    for(auto const& e : v) v2.push_back( lexicographic_pair_helper(e, maxDigits) );
    
    std::cout << "pairs: ";
    for(auto const& e : v2) std::cout << e.first <<':'<<e.second << ", ";
    std::cout << "\n\n";
    
    std::sort(begin(v2), end(v2), [](std::pair<int, int> const& l, std::pair<int, int> const& r)
                                  { if(l.first < r.first) return true; if(l.first > r.first) return false; return l.second < r.second; });
    
    std::cout << "unsorted: ";
    for(auto const& e : v) std::cout << e << ", ";
    std::cout << "\n\n";
    
    std::cout << "sorted: ";
    for(auto const& e : v2) std::cout << e.second << ", ";
    std::cout << "\n\n";
}