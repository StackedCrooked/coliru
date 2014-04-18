#include<vector>
#include<algorithm>
#include<string>

// I wish to return a vector of these as the result
struct StructC {
    std::string mCommonField;
    std::string mNameFromA; // cherry picked from StructA
    std::string mNameFromB; // cherry picked from StructB
    float mFloatFromA;      // cherry picked from StructA
    int mIntFromB;          // cherry picked from StructB
};

struct StructA {
    // conversion operator from StructA to StructC
    operator StructC() { return { mCommonField, mNameAString, "[]", mFloatValueA, 0 }; }
    std::string mCommonField;
    std::string mNameAString;
    float mFloatValueA;
};

struct StructB {
    // conversion operator from StructB to StructC
    operator StructC() { return { mCommonField, "[]", mNameBString, 0.0f, mIntValueB }; }
    std::string mCommonField;
    std::string mNameBString;
    int mIntValueB;
};

#include <iostream>
#include <iterator>

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, StructC const& sc) {
    return os << sc.mCommonField << " - " << sc.mNameFromA << " - " 
       << sc.mNameFromB << " - " << std::fixed << sc.mFloatFromA << " - " << sc.mIntFromB << std::endl;
}

int main() {
    struct Common {
        std::string const& mCommonField;
        Common(StructA const& sa) : mCommonField{sa.mCommonField} {};
        Common(StructB const& sb) : mCommonField{sb.mCommonField} {};
    };
    auto comparator = [](Common const& lhs, Common const& rhs) { return lhs.mCommonField < rhs.mCommonField; };

    // initially unsorted list of StructA
    std::vector<StructA> aStructs = {{"hello", "nameA1", 1.0f}, {"goodbye", "nameA2", 2.0f}, {"foo", "nameA3", 3.0f}};
    // initially unsorted list of StructB
    std::vector<StructB> bStructs = {{"hello", "nameB1", 10}, {"goodbye", "nameB2", 20}, {"bar", "nameB3", 30}};

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