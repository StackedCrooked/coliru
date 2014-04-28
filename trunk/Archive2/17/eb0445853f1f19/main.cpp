#include <algorithm>
#include <iostream>
#include <iterator>

template<typename It, typename Elem>
bool in_any_interval(It first, It last, const Elem &val) {
    return std::any_of(first, last, [&val](const auto &p) {
        return p.first <= val && val <= p.second;
    });
}

int main() {
    std::pair<int, int> intervals[]{
        {11, 20}, {31, 40}, {51, 60}, {71, 80}, {91, 100}
    };
    
    const int num = 15;
    std::cout << in_any_interval(std::begin(intervals), std::end(intervals), num);
}