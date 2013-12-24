#include <cmath>
#include <iostream>

double GraphMath(double data1, double data2)
{
     double d1 = data2 / data1;
     double d2 = log10(d1);
     double d3 = 1000 * d2;
     return d3;
     //return 1000 * log10(data2 / data1);
}

double GraphMath2(double data1, double data2)
{
     double d1 = data2 / data1;
     double d2 = log10(d1);
     double d3 = 1000 * d2;
     //return d3;
     return 1000 * log10(data2 / data1);
}

int main() {
    std::cout << GraphMath(4500, 4497) << '\n';
    std::cout << GraphMath2(4500, 4497) << '\n';
}