#include <iostream>

template<int M, int K, int S> struct Unit { // a unit in the MKS system
    enum { m=M, kg=K, s=S };
};

template<typename Unit> // a magnitude with a unit
struct Value {
    double val; // the magnitude
    constexpr explicit Value(double d) : val(d) {} // construct a Value from a double
};

using Meter = Unit<1,0,0>; // unit: meter
using Second = Unit<0,0,1>; // unit: sec
using Speed = Value<Unit<1,0,-1>>; // meters/second type

constexpr Value<Second> operator "" _s(long double d) // a f-p literal suffixed by ‘_s’
{
    return Value<Second> (d);
}
constexpr Value<Meter> operator "" _m(long double d) // a f-p literal suffixed by ‘_m’
{
    return Value<Meter> (d);
}

constexpr Value<Meter> operator "" _m(unsigned long long d) // an integral literal suffixed by ‘_m’
{
    return Value<Meter> (d);
}

template<int m1, int k1, int s1, int m2, int k2, int s2>
Value<Unit<m1 - m2, k1 - k2, s1 - s2>> operator / (Value<Unit<m1, k1, s1>> a, Value<Unit<m2, k2, s2>> b)
{
    return Value<Unit<m1 - m2, k1 - k2, s1 - s2>>(a.val / b.val);
}

int main()
{
    Speed sp1 = 100_m / 9.8_s;
    std::cout << sp1.val;
}
