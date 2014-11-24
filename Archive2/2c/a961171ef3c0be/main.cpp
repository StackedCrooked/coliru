#include <cmath>
#include <iostream>

namespace {
    double maclaurin_cos(double x, double abs_error, size_t &n) {
        //from http://hashcode.ru/questions/377753
        double sum = 0;
        double an = 1;
        n = 1;
        do
        {
                sum += an;
                n   += 1;
                an *= (-1)*(x*x/(2.0*n*2*(n - 1)));
        }
        while(abs_error <= std::abs(an));
        return sum;
    }
}

int main()
{
    double xstart, xend, dx, abs_error;
    std::cin >> xstart >> xend >> dx >> abs_error;
    std::cout << xstart << " " << xend << " " << dx << " " << abs_error << std::endl;
    for (double x = xstart; x < xend; x += dx) {
        size_t n;
        double cos_2x = maclaurin_cos(2*x, abs_error, n), cossq_x = 0.5 * (1.0 + cos_2x),
            exact_cos = cos(2*x), exact_cossq = cos(x)*cos(x);
        std::cout << "cos(" << 2*x << ")   = " << cos_2x
            << "; n=" << n << "; rel.error=" << (1e2*(cos_2x - exact_cos) / exact_cos) << "%\n";        
        std::cout << "cos^2(" << x << ") = " << cossq_x
            << "; n=" << n << "; rel.error=" << (1e2*(cossq_x - exact_cossq) / exact_cossq) << "%" << std::endl;
    }
}
