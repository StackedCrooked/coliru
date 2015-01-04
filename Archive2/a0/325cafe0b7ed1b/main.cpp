#include <iostream>
#include <complex>

using complex = std::complex< long double >;

// used as conversion
constexpr complex operator"" _i ( long double imm )
{
    return complex(0, imm);
}

complex pow(const complex& arg, long power) {
    if(power == 0) return 1;
    if(power == 1) return arg;
    
    auto half = pow(arg, power/2);
    
    if(power & 1) return half * half * arg;
    else return half * half;
}

double fac(unsigned long long value) {
    enum{ MAX = 255 };
    static double mem[MAX+1] = {1, 0};
    if(mem[value]) return mem[value];
    else return mem[value] = fac(value-1) * value;
}

template<class T>
T my_abs(const T& value) {
    if(value < T(0)) return -value;
    else return value;
}

template<class T>
T my_exp(const T& value) {
    T accum = 1;
    T accum_pow = 1;
    auto accum_fac = 1ULL;
    T interm;
    for(auto i = 1ULL; i < 20; ++i) {
        accum_pow *= value;
        accum_fac *= i;
        interm = accum_pow / (long double)accum_fac;
        accum += interm;
        // if(my_abs(interm) < T(0.000000001)) break;
    }
    
    return accum;
}

int main()
{
	std::cout << my_exp(8.0_i) << std::endl;
    std::cout << std::sin(8.0) << std::endl;

}