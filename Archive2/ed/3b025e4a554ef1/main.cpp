#include <utility>

template <char... s> struct silly { using type = int; };
template <char... s> struct silly<'1', s...> { using type = double; };

template <char... s>
typename silly<s...>::type operator"" _silly() { return 0; }

int main()
{
    static_assert(std::is_same<int, decltype(4321_silly)>::value, "no luck");
	static_assert(std::is_same<double, decltype(1234_silly)>::value, "no luck");
}