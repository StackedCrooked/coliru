#include <type_traits>
#include <cassert>
#include <utility>

template <typename T>
using Invoke = typename T::type;

template<typename T>
using RemoveCRef = Invoke<std::remove_const<Invoke<std::remove_reference<T>>>>;


template<typename T>
constexpr auto max_impl(T&& a, T&& b, std::true_type) -> decltype(a < b ? b : a)
{
    return a < b ? b : a;
}

template<typename T>
constexpr auto max_impl(T&& a, T&& b, std::false_type) -> decltype(RemoveCRef<T>(a < b ? b : a))
{
    return a < b ? b : a;
}


template<typename A>
constexpr auto Max(A&& a1, A&& a2) -> decltype(max_impl(a1, a2, std::is_lvalue_reference<A>()))
{
    return max_impl(a1, a2, std::is_lvalue_reference<A>());
}


template<typename A, typename B>
constexpr auto Max(A&& a, B&& b) -> decltype(max_impl(B(a), b, std::false_type()))
{
    return max_impl(B(a), b, std::false_type());
}

template<typename A, typename B>
constexpr auto Max(A&& a, B&& b) -> decltype(max_impl(a, A(b), std::false_type()))
{
    return max_impl(a, A(b), std::false_type());
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

