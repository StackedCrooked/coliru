#include <iostream>
#include <algorithm>
#include <vector>

double f1(double x){
    return x * 1.7;
}

template <typename F>
std::vector<double> calc (std::vector<double> const& a, F f) {
    std::vector<double> b(a.size());
    std::transform(a.begin(), a.end(), b.begin(), f);
    return b;
}

int main()
{
    std::vector<double> a { 0,1,2,3,4,5,6,7,8,9 };

    for (auto d : calc(a, f1))
        std::cout << d << " ";
}
