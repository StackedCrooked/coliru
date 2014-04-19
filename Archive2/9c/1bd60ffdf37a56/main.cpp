#include<vector>
#include<algorithm>
#include<string>

// I wish to return a vector of these as the result
struct StructC {
    std::string mCommonField;
    std::string mNameFromA; // cherry picked from StructA
    std::string mNameFromB; // cherry picked from StructA
};

struct StructA {
    // conversion operator from StructA to StructC
    operator StructC() { return { mCommonField, mNameString, "" }; }
    std::string mCommonField;
    std::string mNameString;
    int mValueA;
};

struct StructB {
    std::string mCommonField;
    std::string mNameString;
    std::string mFooString;
};

#include <iostream>
#include <iterator>

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, StructC const& sc) {
    return os << sc.mCommonField << " - " << sc.mNameFromA << " - " << sc.mNameFromB << std::endl;
}

int main() {
    struct Common {
        std::string const& mCommonField;
        Common(StructA const& sa) : mCommonField{sa.mCommonField} {};
        Common(StructB const& sb) : mCommonField{sb.mCommonField} {};
    };
    auto comparator = [](Common const& lhs, Common const& rhs) { return lhs.mCommonField < rhs.mCommonField; };

    // initially unsorted list of StructA
    std::vector<StructA> aStructs = {{"hello", "nameA1", 1}, {"goodbye", "nameA2", 3}, {"foo", "nameA3", 5}};
    // initially unsorted list of StructB
    std::vector<StructB> bStructs = {{"hello", "nameB1", "foo1"}, {"goodbye", "nameB2", "foo2"}, {"bar", "nameB3", "foo3"}};

    // in the above list, "hello" & "goodbye" are the common in both aStructs & bStructs    
    

    // pre-sort both sets before calling std::intersection
    std::sort(aStructs.begin(), aStructs.end(), comparator);
    std::sort(bStructs.begin(), bStructs.end(), comparator);
    
    std::vector<StructC> intersection;
    std::set_intersection(aStructs.begin(), aStructs.end(),
                          bStructs.begin(), bStructs.end(),
                          std::back_inserter(intersection),
                          comparator);
    
    std::copy(intersection.begin(), intersection.end(),
              std::ostream_iterator<StructC>(std::cout, ""));
    return 0;
}