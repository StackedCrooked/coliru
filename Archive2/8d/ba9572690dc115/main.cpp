#include <cmath>
#include <iostream>

template<typename T>
T romberg(const int n, const int k, const T h, const T a = 0.0, const T b = 1.0) {
    auto hfunc = [=](int i){
        return h / std::pow(2, i);
    };
    auto ffunc = [](double x) {
        return 1 / (1 + x);
    };
    //std::cout << hfunc(1)/2 << " " << ffunc(a) << " " << ffunc(b) << std::endl;
    if (n == 1 && k == 1)
        return (hfunc(1)/2) * (ffunc(a) + ffunc(b));
    if (n == 1) {
        double res = 0;
        int htop = hfunc(1) / hfunc(n) - 1;
        for (int i = 1; i <= htop; ++i)
            res += ffunc(a + i * hfunc(n));
        res = ffunc(a) + ffunc(b) + 2 * res;
        return (hfunc(n)/2) * res;
    }
    T npluskminus = romberg(n+1, k-1, h);
    T nkminus = romberg(n, k-1, h);
    T denom = std::pow(hfunc(n) / hfunc(n+1), 2*k-1) - 1;
    return npluskminus + (npluskminus - nkminus) / denom;
}

int main() {
    std::cout << romberg(1, 1, 0.5) << std::endl;
    std::cout << romberg(1, 2, 0.5) << std::endl;
}