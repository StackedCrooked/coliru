#include <vector>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>


template<class InputR1, class InputR2>
auto delta_rng(InputR1 const& rng1, InputR2 const& rng2)
{
    auto x = rng1 | boost::adaptors::transformed(
        [i = 0](const int&) mutable {
        return 0;
    });
}

int main()
{
    std::vector<int> v1, v2;
    delta_rng(v1, v2);
}
