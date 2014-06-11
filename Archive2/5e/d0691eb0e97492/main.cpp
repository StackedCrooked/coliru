#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iostream>
    
template<typename RanIter>
std::pair<RanIter, RanIter> do_search(RanIter first, RanIter last)
{
    // first look for 2 consecutive Us
    auto it = std::search_n(first, last, 2, "U");
    
    if(it == last) {
        // nothing to replace, bail
        return std::make_pair(last, last);
    }
    
    // check if we have 3 consecutive Us
    if(std::distance(it, last) >= 3) {
        // there are at least 3 elements in the range, it's ok to check
        if(*std::next(it, 2) == "U") {
            return std::make_pair(it, std::next(it, 3));
        }
    }
    
    return std::make_pair(it, std::next(it, 2));
}

int main()
{
    std::vector<std::string> vec{"A", "B", "C", "U", "U", "D", "U", "U", "U", "U", "E", "U", "U"};
    
    auto first = vec.begin();
    while(first != vec.end()) {
        auto result = do_search(first, vec.end());
        first = result.first;
        if(first == vec.end()) {
            break;
        }
        
        auto dist = std::distance(first, result.second);
        if(dist == 3) {
            first = vec.insert(first, "U'");
        } else {
            first = vec.insert(first, "U2");
        }
        
        // advance first to the first element to be removed and erase them
        std::advance(first, 1);
        first = vec.erase(first, std::next(first, dist));
    }
    
    for(auto const& v : vec) {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
}
