#include <cassert>
#include <iostream>


template<typename T>
struct Clamp_A
{
    Clamp_A(T a) : a(a) {}
    
    T operator()(T x) const
    {
        return x < a ? a : x;
    }
    
    T a;
};


template<typename T>
auto make_lbound(T a)
{
    return Clamp_A<T>{a};
}


template<typename T>
struct Clamp_B
{
    Clamp_B(T b) : b(b) {}
    
    T operator()(T x) const
    {
        return b < x ? b : x;
    }
    
    T b;
};


template<typename T>
auto make_ubound(T b)
{
    return Clamp_B<T>{b};
}


template<typename T>
struct Clamp_AB
{
    Clamp_AB(T a, T b):  a(a), b(b) {}
    
    T operator()(T x) const
    {
        return a(b(x));
    }
    
    Clamp_A<T> a;
    Clamp_B<T> b;
};

template<typename T>
auto make_bounded(T a, T b)
{
    return Clamp_AB<T>{a, b};
}
    
int main()
{
    auto min_20 = make_lbound(20);
    assert(min_20(21) == 21);
    assert(min_20(20) == 20);
    assert(min_20(19) == 20);
    
    auto max_30 = make_ubound(30);
    assert(max_30(29) == 29);
    assert(max_30(30) == 30);
    assert(max_30(31) == 30);
    
    auto interval_10_20 = make_bounded(10, 20);
    assert(interval_10_20(9 ) == 10);
    assert(interval_10_20(10) == 10);
    assert(interval_10_20(15) == 15);
    assert(interval_10_20(20) == 20);
    assert(interval_10_20(21) == 20);
}



