#include <type_traits>
#include <cassert>
#include <utility>

template<typename T, typename U> constexpr auto Min(T&& lhs, U&& rhs)  {
    return lhs < rhs ? std::forward<T>(lhs) : std::forward<U>(rhs);
}
template<typename T, typename U> constexpr decltype(auto) Min(T& lhs, U& rhs)  {
    return lhs < rhs ? lhs : rhs;
}
template<typename T, typename U> constexpr auto Max(T&& lhs, U&& rhs)  {
    return lhs < rhs ? std::forward<T>(rhs) : std::forward<U>(lhs);
}
template<typename T, typename U> constexpr decltype(auto) Max(T& lhs, U& rhs)  {
    return lhs < rhs ? rhs : lhs;
}


struct Nocopy
{
    constexpr Nocopy(int a) : a(a) {}

    Nocopy(const Nocopy&) = delete;
    Nocopy& operator=(const Nocopy&) = delete;

    friend constexpr bool operator<(const Nocopy& lhs, const Nocopy& rhs)
    {
        return lhs.a < rhs.a;
    }

    friend constexpr bool operator==(const Nocopy& lhs, const Nocopy& rhs)
    {
        return lhs.a == rhs.a;
    }

    int a;
};


#include <iostream>


int main()
{
    // must not return dangling reference
    static_assert(!std::is_reference<decltype(Max(1, 2))>::value, "");
    static_assert(!std::is_reference<decltype(Max(2, 1))>::value, "");

    static_assert(Max(1, 2) == 2, "");
    static_assert(Max(2, 1) == 2, "");

    constexpr int a = 1;
    constexpr int b = 2;
    static_assert(std::is_lvalue_reference<decltype(Max(a, b))>::value, "");
    static_assert(Max(a, b) == b, "");
    static_assert(Max(a, b) == 2, "");


    constexpr Nocopy nocopy1{1}, nocopy2{2};
    static_assert(std::is_lvalue_reference<decltype(Max(nocopy1, nocopy2))>::value, "");
    static_assert(Max(nocopy1, nocopy2) == nocopy2, "");
    static_assert(Max(nocopy2, nocopy1) == nocopy2, "");


    std::string s1 = "s1", s2 = "s2";
    assert(Max(s1, s2) == s2);
    assert(Max(s2, s1) == s2);

    static_assert( std::is_lvalue_reference<decltype(Max(s1, s2))>::value, "");
    static_assert(!std::is_reference<decltype(Max("", s2))>::value, "");
    static_assert(!std::is_reference<decltype(Max(s1, ""))>::value, "");

    std::cout << "OK\n";

}

