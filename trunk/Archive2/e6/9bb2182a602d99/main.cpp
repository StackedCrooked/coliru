#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;

int main() {
    double ip, d = nextafter(1., .0);
    cout << 15 << ": " <<setprecision(15)
        << abs(d) << " " << modf(abs(d), &ip) << '\n';
    cout << std::numeric_limits<double>::max_digits10 << ": "
        << setprecision(std::numeric_limits<double>::max_digits10)
        << abs(d) << " " << modf(abs(d), &ip) << '\n';
}