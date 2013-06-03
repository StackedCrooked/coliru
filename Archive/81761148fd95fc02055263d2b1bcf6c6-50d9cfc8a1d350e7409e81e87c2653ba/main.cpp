#include <annex/range/source/istream.hpp>
#include <annex/range/source/interval.hpp>
#include <annex/range/composite/map.hpp>
#include <annex/range/composite/filter.hpp>
#include <annex/range/composite/zip.hpp>

#include <annex/functional/compose.hpp>
#include <annex/functional/curry.hpp>

#include <fstream>
#include <iostream>

// Hack for printing tuples because I'm lazy
#include <annex/tuple/algorithms.hpp>
namespace std { using annex::tuples::operator<<; }

int main()
{
    namespace range = annex::range;
    namespace R = annex::range_operators;
    using annex::compose;
    using annex::curry;

    auto pipeline = compose(
            curry(R::zip {}, range::integers())
            , curry(R::filter {}, [](int i) { return i % 3 == 0; })
            , curry(R::map {}, [](int i) { return 2 * i; })
            );

    std::ifstream input { "lol.dat" };
    auto r = pipeline(range::istream<int>(input));
    for(auto&& e: r)
        std::cout << e << '\n';
}