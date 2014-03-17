#include<vector>
#include<algorithm>
#include<string>

// common field used for set intersection
struct StructA {
    std::string mCommonField;
    float mFloatValue;
};

struct StructB {
    std::string mCommonField;
    int mValue1;
    short mValue2;
};

#include <iostream>
#include <iterator>

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, StructA const& sa) {
    return os << sa.mCommonField << " - " << sa.mFloatValue << std::endl;
}

int main() {
    auto cmp = [](auto lhs, auto rhs) { return lhs.mCommonField < rhs.mCommonField; };

    // initially unsorted list
    std::vector<StructA> aStructs = {{"hello", 1.0f}, {"goodbye", 2.0f}, {"foo", 3.0f}};
    // initially unsorted list
    std::vector<StructB> bStructs = {{"hello", 1, 2}, {"goodbye", 3, 4}, {"bar", 5, 6}};
    // sorting both sets before calling std::intersection
    std::sort(aStructs.begin(), aStructs.end(), cmp);
    std::sort(bStructs.begin(), bStructs.end(), cmp);

    std::vector<StructA> intersection;
    std::set_intersection(aStructs.begin(), aStructs.end(),
                          bStructs.begin(), bStructs.end(),
                          std::back_inserter(intersection),
                          cmp);
    
    std::copy(intersection.begin(), intersection.end(),
              std::ostream_iterator<StructA>(std::cout, ""));
    
    return 0;
}