#include <array>
#include <unordered_set>
#include <numeric>

//compute sum of numbers below N which are multiples of any number in M
template <typename T, typename... M>
T SumFizzBuzz(size_t N, M... m)
{
    const size_t ms = sizeof...(M);
    std::array<T, ms> multipliers = { m... };

    //construct all multiples
    std::unordered_set<T> multiples;
    for (auto& t : multipliers)
    {
        for (size_t n = 1; (t*n) < N; n++)
        {
            multiples.insert(t*n);
        }
    }

    //sum them :v
    return std::accumulate(multiples.begin(), multiples.end(), T(0));
}

#include <iostream>
int main()
{
    auto sum = SumFizzBuzz<unsigned>(1000, 3, 5);
    std::cout << sum << "\n";
}