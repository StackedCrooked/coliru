#include <iostream>
#include <cmath>
#include <random>

double f(double x, double a, double b, double c)
{
    return sin((a*x / (1.0 + pow(x, 2))) + 1.0) * atan(b*x - 1.0 / 2.0) + exp(-c*x) * atan(x);
}

double BisectionMethod(double f(double, double, double, double), double a, double b, double c)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static const auto lower_bound = -1.0;
    static const auto upper_bound =  1.0;
    static std::uniform_real_distribution<> dis(lower_bound, upper_bound);

    auto pos_pt = dis(gen);
    auto neg_pt = dis(gen);

    while (f(pos_pt, a, b, c) < 0.0)
        pos_pt = dis(gen);

    while (f(neg_pt, a, b, c) > 0.0)
        neg_pt = dis(gen);

    static const auto about_zero_mag = 1E-8;
    for (;;)
    {
        const auto mid_pt = (pos_pt + neg_pt)/2.0;
        const auto f_mid_pt = f(mid_pt, a, b, c);
        if (fabs(f_mid_pt)  < about_zero_mag)
            return mid_pt;

        if (f_mid_pt >= 0.0)
            pos_pt = mid_pt;
        else
            neg_pt = mid_pt;
    }
}

int main()
{
    double a, b, c;

    a =10, b = 2.0, c = 0.0;
    const auto root1 = BisectionMethod(f, a, b, c);
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    std::cout << "Found root: (" << root1 << ", " << f(root1, a, b, c) << ")" << std::endl;

    a =4.5, b = 2.8, c = 1.0;
    const auto root2 = BisectionMethod(f, a, b, c);
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    std::cout << "Found root: (" << root2 << ", " << f(root2, a, b, c) << ")" << std::endl;
}