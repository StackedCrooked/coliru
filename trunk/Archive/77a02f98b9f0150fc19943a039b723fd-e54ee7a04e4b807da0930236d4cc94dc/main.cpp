    #include <algorithm>
    #include <vector>
    #include <boost/range.hpp>
    #include <boost/range/adaptors.hpp>
    #include <boost/range/algorithm.hpp>
    #include <iostream>

    int main()
    {
        std::vector<int> v {1, 2, 3, 4, 5, 6};
        std::vector<int> r;

        namespace rng = boost::adaptors;

        boost::transform(
            v | rng::strided(2),
            std::make_pair(v.begin() + 1, v.end()) | rng::strided(2),
            std::back_inserter(r),
            [] (int a, int b) { return a + b; });

        for (auto i : r) { std::cout << i << " "; }
    }
