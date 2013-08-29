#include <iostream>


template<typename T>
struct LowerBound
{
    LowerBound(T a) : a(a) {}
    
    T operator()(T x) const
    {
        return x < a ? a : x;
    }
    
    T a;
};


template<typename T>
auto clamp_lower(T a)
{
    return LowerBound<T>{a};
}


template<typename T>
struct UpperBound
{
    UpperBound(T b) : b(b) {}
    
    T operator()(T x) const
    {
        return b < x ? b : x;
    }
    
    T b;
};


template<typename T>
auto clamp_upper(T b)
{
    return UpperBound<T>{b};
}

template<typename T>
auto operator&& (const LowerBound<T>& lbound, const UpperBound<T>& ubound)
{
    struct Combine
    {
        Combine(const LowerBound<T>& lbound, const UpperBound<T>& ubound) : l(lbound), u(ubound) {}
        T operator()(T t) const
        {
            return l(u(t));
        }
        
        LowerBound<T> l;
        UpperBound<T> u;
        
    };
    return Combine{lbound, ubound};
}


struct X
{
}x;

template<typename T>
auto operator<=(X x, T t)
{
    return clamp_upper(t);
}

template<typename T>
auto operator<=(T t, X x)
{
    return clamp_lower(t);
}

template<typename L, typename T>
auto operator<=(L l, T t)
{
    return l && clamp_upper(t);
}

#define ASSERT_EQ(a, b) std::cout << #a << " == " << #b << std::flush << " => " << ((a) == (b) ? "PASS" : "FAIL") << std::endl;
    
int main()
{
    std::cout << "\ntesting lbound" << std::endl;
    auto round_up_to_20 = clamp_lower(20);
    ASSERT_EQ(round_up_to_20(19), 20);
    ASSERT_EQ(round_up_to_20(20), 20);
    ASSERT_EQ(round_up_to_20(21), 21);
    
    std::cout << "\ntesting ubound" << std::endl;
    auto round_down_to_30 = clamp_upper(30);
    ASSERT_EQ(round_down_to_30(29), 29);
    ASSERT_EQ(round_down_to_30(30), 30);
    ASSERT_EQ(round_down_to_30(31), 30);
    
    std::cout << "\ncombined" << std::endl;
    auto between_20_30 = round_up_to_20 && round_down_to_30;
    ASSERT_EQ(between_20_30(19), 20);
    ASSERT_EQ(between_20_30(20), 20);
    ASSERT_EQ(between_20_30(25), 25);
    ASSERT_EQ(between_20_30(30), 30);
        
    std::cout << "x <= 10" << std::endl;
    ASSERT_EQ((0 <= x)(-1), 0);
    ASSERT_EQ((0 <= x)(0), 0);
    
    ASSERT_EQ((x <= 9)(9), 9);
    ASSERT_EQ((x <= 9)(10), 9);
    
    ASSERT_EQ((0 <= x <= 9)(-1), 0);
    ASSERT_EQ((0 <= x <= 9)(0), 0);
    ASSERT_EQ((0 <= x <= 9)(5), 5);
    ASSERT_EQ((0 <= x <= 9)(9), 9);
    ASSERT_EQ((0 <= x <= 9)(10), 9);
}




