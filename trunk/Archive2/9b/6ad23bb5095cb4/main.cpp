#include <iostream>
#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval.hpp>

namespace icl = boost::icl;

int main()
{
    icl::interval_map<double, int,
       icl::partial_absorber,
       /*ICL_COMPARE Compare =*/ ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, double), 
       /*ICL_COMBINE Combine =*/ ICL_COMBINE_INSTANCE(icl::inplace_plus, int), 
       /*ICL_SECTION Section =*/ ICL_SECTION_INSTANCE(icl::inter_section, int)
        > joined_map;
    using ival = icl::interval<double>;

    joined_map.add({ival::open(1., 2.), 1});
    joined_map.add({ival::open(3., 5.), 2});
    std::cout << "#1: "; for (auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";
    auto clone1 = joined_map;

    joined_map.add({3., 2});
    std::cout << "#2: "; for (auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";
    auto clone2 = joined_map;

    joined_map.add({3., 2});
    std::cout << "#3: "; for (auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";
    auto clone3 = joined_map;

    joined_map.add({ival::open(0., 6.), 10});
    std::cout << "#4: "; for (auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";
    auto clone4 = joined_map;

    for (double x = 0; x < 7; x += .5)
    {
        std::cout << x
            << "\t" << clone1(x)
            << "\t" << clone2(x)
            << "\t" << clone3(x)
            << "\t" << clone4(x) 
            << "\n";
    }
}
