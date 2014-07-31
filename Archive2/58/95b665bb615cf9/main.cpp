#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <boost/iterator/counting_iterator.hpp>

template<class Range, class T, class BinaryOp>
void self_transform(Range& rng, T value, BinaryOp op)
{
    auto i = value;
    for (auto& elem : rng) {
        elem = op(elem, i);        
        ++i;
    }
}

int main()
{    
    std::list<std::string> items = { "hello", "world!" };
    
    // add 0 and 1 after the two words
    self_transform(items, 0, [](auto const& elem, auto i) {
        return elem + std::to_string(i);    
    });
    
    // add another 0 and 1
    std::transform(
        begin(items), end(items), 
        boost::counting_iterator<int>(0), 
        begin(items), 
        [](auto const& elem, auto i) {
        return elem + std::to_string(i);    
    });
    
    // hello00 and world!11
    for (auto const& item : items) 
        std::cout << item << '\n';
}
