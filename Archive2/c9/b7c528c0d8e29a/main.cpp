#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <utility>

template<class FwdIt, class OutIt, class UnaryPred>
auto find_all_if(FwdIt first, FwdIt last, OutIt dst, UnaryPred pred)
{   
    while (first != last) {
        // start of next occurance
        auto next_b = std::find_if(first, last, pred);
        if (next_b == last) break;
        
        // end of next occurance
        auto next_e = std::find_if_not(next_b, last, pred);
        *dst++ = make_pair(next_b, next_e);
        
        first = next_e;
    }
    return dst;
}

int main()
{
    auto const v = std::vector<int> { 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1 };
    using It = decltype(v.begin());
    std::vector<std::pair<It, It>> r; // "range of ranges" 
    
    find_all_if(begin(v), end(v), std::back_inserter(r), 
        [](auto e) { return e == 1; }
    );
    
    for (auto&& e : r) {
        std::cout << "[";
        std::cout << std::distance(begin(v), e.first) << ", ";
        std::cout << std::distance(begin(v), e.second) << "), ";
    }
}