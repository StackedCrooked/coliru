#include <cstddef>
#include <tuple>

template<std::size_t I, typename... Args>
using At = typename std::tuple_element<I, std::tuple<Args...>>::type;

template<typename T, typename U>
constexpr bool IsSame{std::is_same<T, U>::value};

int main() {
    static_assert(IsSame<At<0, int>, int>, "");
    static_assert(IsSame<At<0, int, char>, int>, "");
    static_assert(IsSame<At<1, int, char>, char>, "");
}