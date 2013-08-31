#include <iostream>


template<typename T>
struct AtLeast
{
    AtLeast(T a) : a(a) {}
    
    T operator()(T x) const
    {
        return x < a ? a : x;
    }
    
    T a;
};


template<typename T>
auto at_least(T a)
{
    return AtLeast<T>{a};
}


template<typename T>
struct AtMost
{
    AtMost(T b) : b(b) {}
    
    T operator()(T x) const
    {
        return b < x ? b : x;
    }
    
    T b;
};


template<typename T>
auto at_most(T b)
{
    return AtMost<T>{b};
}


template<typename T>
auto operator&& (const AtLeast<T>& lbound, const AtMost<T>& ubound)
{
    struct Combine
    {
        Combine(const AtLeast<T>& lbound, const AtMost<T>& ubound) : l(lbound), u(ubound) {}
        T operator()(T t) const
        {
            return l(u(t));
        }
        
        AtLeast<T> l;
        AtMost<T> u;
        
    };
    return Combine{lbound, ubound};
}

#define ASSERT_EQ(a, b) std::cout << #a << " == " << #b << std::flush << " => " << ((a) == (b) ? "PASS" : "FAIL") << std::endl;
    
int main()
{
    std::cout << "\ntesting lbound" << std::endl;
    auto min_20 = at_least(20);
    ASSERT_EQ(min_20(19), 20);
    ASSERT_EQ(min_20(20), 20);
    ASSERT_EQ(min_20(21), 21);
    
    std::cout << "\ntesting ubound" << std::endl;
    auto max_30 = at_most(30);
    ASSERT_EQ(max_30(29), 29);
    ASSERT_EQ(max_30(30), 30);
    ASSERT_EQ(max_30(31), 30);
    
    std::cout << "\ncombined" << std::endl;
    auto between_20_30 = min_20 && max_30;
    ASSERT_EQ(between_20_30(19), 20);
    ASSERT_EQ(between_20_30(20), 20);
    ASSERT_EQ(between_20_30(25), 25);
    ASSERT_EQ(between_20_30(30), 30);
}




