#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double ip, d = nextafter(1., .0);
    cout << setprecision(15) << abs(d) << " " << modf(abs(d), &ip) << endl;
    cout << setprecision(20) << abs(d) << " " << modf(abs(d), &ip) << endl;
}