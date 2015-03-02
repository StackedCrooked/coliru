#include <initializer_list>
#include <numeric>

template<typename Range>
auto Σ(Range&& range)
-> decltype( std::accumulate(std::begin(range), std::end(range), 0) )
{
    // No time for ADL! Or figuring out the right accumulator type!
    return std::accumulate(std::begin(range), std::end(range), 0);
}

int main()
{
    auto a = { 0, 1, 2, 3, 4, 5 };
    return Σ(a);
}