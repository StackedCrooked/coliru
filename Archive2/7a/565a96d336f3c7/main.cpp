#include <iostream>
#include <sstream>
#include <tuple>
#include <array>

namespace detail
{
    template<int... Is>
    struct seq { };

    template<int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

    template<int... Is>
    struct gen_seq<0, Is...> : seq<Is...> { };

    template<int... Ts>
    static constexpr std::pair<int, int> factorial(detail::seq<Ts...>, int sum = 0, int fact = 1)
    {
        typedef int pack[sizeof...(Ts)];
        (void)pack{ [&]() { fact *= (Ts + 1); sum += fact; return 0; }() ... };

        return std::make_pair(fact, sum);
    }
}

template<int N>
static constexpr std::pair<int, int> factorial()
{
    return detail::factorial(detail::gen_seq<N>());
}

int main()
{
    auto p = factorial<3>();
    std::cout << "Factorial: " << p.first << '\n'
              << "Sum: "       << p.second;
}