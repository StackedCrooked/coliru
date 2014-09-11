#include <type_traits>
#include <utility>

// Using Martinho's type traits
// http://flamingdangerzone.com/cxx11/2013/02/25/even-more-traits.html
template <typename T>
using Invoke = typename T::type;

template <typename ...T>
using CommonType = Invoke<std::common_type<T...>>;


template<typename ...Args>
constexpr auto Max(Args ...args) -> CommonType<Args...>;


namespace Detail
{    
    // helper
    template<typename T>
    constexpr T MaxImpl(T a)
    { return a; }
        
    // if a and b have same type
    template<typename T>
    constexpr T MaxImpl(T a, T b)
    { return a < b ? b : a; }
    
    
    template<typename A, typename B>
    constexpr auto MaxImpl(A a, B b) -> CommonType<A, B>
    {
        // make types the same
        using R = CommonType<A, B>;
        return MaxImpl(R(a), R(b));
    }
    
    template<typename A, typename B, typename ...Tail>
    constexpr auto MaxImpl(A a, B b, Tail ...tail) -> CommonType<A, B, Tail...>
    {
        using R = CommonType<A, B, Tail...>;
        return MaxImpl(Max(a, b), Max(tail...));
    }
}


template<typename ...Args>
constexpr auto Max(Args ...args) -> CommonType<Args...>
{
    return Detail::MaxImpl(args...);
}


int main()
{
    #define ASSERT_EQ(a, b) static_assert(a == b, "");
    
    ASSERT_EQ(Max(1, 2), 2);
    ASSERT_EQ(Max(2, 1), 2);
    ASSERT_EQ(Max(1, 2, 3), 3);
    ASSERT_EQ(Max(1, 3, 2), 3);
    ASSERT_EQ(Max(3, 1, 2), 3);
    ASSERT_EQ(Max(3, 2, 1), 3);
    
    ASSERT_EQ(Max(1, 2, 3, 4), 4);
    ASSERT_EQ(Max(1, 2, 4, 3), 4);
    ASSERT_EQ(Max(1, 4, 2, 3), 4);
    ASSERT_EQ(Max(4, 1, 2, 3), 4);
}

