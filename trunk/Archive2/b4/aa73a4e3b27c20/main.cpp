#include <type_traits>

template <typename T, typename U>
constexpr auto
min1(T&& t, U&& u) -> decltype(t < u ? t : u)
{
    return t < u ? t : u;
}

template <typename T, typename U>
constexpr auto
min2(T&& t, U&& u)
{
    return t < u ? t : u;
}

int main()
{
    using namespace std;

    static_assert(is_same<decltype(min1(10,2)), int&>::value, "");
    static_assert(is_same<decltype(min2(10,2)), int>::value, "");
}