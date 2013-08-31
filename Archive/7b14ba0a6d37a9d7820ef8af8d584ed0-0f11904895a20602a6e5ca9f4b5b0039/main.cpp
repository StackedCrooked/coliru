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
auto operator<(X x, T t)
{
    return clamp_upper(t - 1);
}

template<typename T>
auto operator<=(T t, X x)
{
    return clamp_lower(t);
}

template<typename L, typename T>
auto operator<(L l, T t)
{
    return l && clamp_upper(t - 1);
}
    
int main()
{   
    std::cout << "Testing 2 <= x" << std::endl;
    for (int i = 0; i != 10; ++i)
    {
        std::cout << i << " => " << (2 <= x)(i) << std::endl;
    }
    
    
    std::cout << "\nTesting x < 4" << std::endl;
    for (int i = 0; i != 10; ++i)
    {
        std::cout << i << " => " << (x < 4)(i) << std::endl;
    }
    
    
    std::cout << "\nTesting 2 <= x < 4" << std::endl;
    for (int i = 0; i != 10; ++i)
    {
        std::cout << i << " => " << (2 <= x < 4)(i) << std::endl;
    }
}




